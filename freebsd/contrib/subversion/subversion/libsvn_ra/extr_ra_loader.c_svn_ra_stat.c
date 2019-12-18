#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_34__ {TYPE_1__* vtable; } ;
typedef  TYPE_3__ svn_ra_session_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_35__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
struct TYPE_36__ {int has_props; int /*<<< orphan*/ * last_author; int /*<<< orphan*/  time; int /*<<< orphan*/  created_rev; int /*<<< orphan*/  size; scalar_t__ kind; } ;
typedef  TYPE_5__ svn_dirent_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_32__ {TYPE_4__* (* stat ) (TYPE_3__*,char const*,int /*<<< orphan*/ ,TYPE_5__**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIRENT_ALL ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_RA_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 TYPE_4__* SVN_NO_ERROR ; 
 char const* SVN_PROP_REVISION_AUTHOR ; 
 char const* SVN_PROP_REVISION_DATE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 TYPE_5__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_4__* stub1 (TYPE_3__*,char const*,int /*<<< orphan*/ ,TYPE_5__**,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_dirent_dup (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_path_is_empty (char const*) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra__dup_session (TYPE_3__**,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_check_path (TYPE_3__*,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_get_dir2 (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_get_repos_root2 (TYPE_3__*,char const**,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_get_session_url (TYPE_3__*,char const**,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_rev_proplist (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 
 TYPE_4__* svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_stat(svn_ra_session_t *session,
                         const char *path,
                         svn_revnum_t revision,
                         svn_dirent_t **dirent,
                         apr_pool_t *pool)
{
  svn_error_t *err;
  SVN_ERR_ASSERT(svn_relpath_is_canonical(path));
  err = session->vtable->stat(session, path, revision, dirent, pool);

  /* svnserve before 1.2 doesn't support the above, so fall back on
     a far less efficient, but still correct method. */
  if (err && err->apr_err == SVN_ERR_RA_NOT_IMPLEMENTED)
    {
      /* ### TODO: Find out if we can somehow move this code in libsvn_ra_svn.
       */
      apr_pool_t *scratch_pool = svn_pool_create(pool);
      svn_node_kind_t kind;

      svn_error_clear(err);

      SVN_ERR(svn_ra_check_path(session, path, revision, &kind, scratch_pool));

      if (kind != svn_node_none)
        {
          const char *repos_root_url;
          const char *session_url;

          SVN_ERR(svn_ra_get_repos_root2(session, &repos_root_url,
                                         scratch_pool));
          SVN_ERR(svn_ra_get_session_url(session, &session_url,
                                         scratch_pool));

          if (!svn_path_is_empty(path))
            session_url = svn_path_url_add_component2(session_url, path,
                                                      scratch_pool);

          if (strcmp(session_url, repos_root_url) != 0)
            {
              svn_ra_session_t *parent_session;
              apr_hash_t *parent_ents;
              const char *parent_url, *base_name;

              /* Open another session to the path's parent.  This server
                 doesn't support svn_ra_reparent anyway, so don't try it. */
              svn_uri_split(&parent_url, &base_name, session_url,
                            scratch_pool);

              SVN_ERR(svn_ra__dup_session(&parent_session, session, parent_url,
                                          scratch_pool, scratch_pool));

              /* Get all parent's entries, no props. */
              SVN_ERR(svn_ra_get_dir2(parent_session, &parent_ents, NULL,
                                      NULL, "", revision, SVN_DIRENT_ALL,
                                      scratch_pool));

              /* Get the relevant entry. */
              *dirent = svn_hash_gets(parent_ents, base_name);

              if (*dirent)
                *dirent = svn_dirent_dup(*dirent, pool);
            }
          else
            {
              apr_hash_t *props;
              const svn_string_t *val;

              /* We can't get the directory entry for the repository root,
                 but we can still get the information we want.
                 The created-rev of the repository root must, by definition,
                 be rev. */
              *dirent = apr_pcalloc(pool, sizeof(**dirent));
              (*dirent)->kind = kind;
              (*dirent)->size = SVN_INVALID_FILESIZE;

              SVN_ERR(svn_ra_get_dir2(session, NULL, NULL, &props,
                                      "", revision, 0 /* no dirent fields */,
                                      scratch_pool));
              (*dirent)->has_props = (apr_hash_count(props) != 0);

              (*dirent)->created_rev = revision;

              SVN_ERR(svn_ra_rev_proplist(session, revision, &props,
                                          scratch_pool));

              val = svn_hash_gets(props, SVN_PROP_REVISION_DATE);
              if (val)
                SVN_ERR(svn_time_from_cstring(&(*dirent)->time, val->data,
                                              scratch_pool));

              val = svn_hash_gets(props, SVN_PROP_REVISION_AUTHOR);
              (*dirent)->last_author = val ? apr_pstrdup(pool, val->data)
                                           : NULL;
            }
        }
      else
        *dirent = NULL;

      svn_pool_clear(scratch_pool);
    }
  else
    SVN_ERR(err);

  return SVN_NO_ERROR;
}
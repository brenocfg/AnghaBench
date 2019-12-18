#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
struct TYPE_21__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_22__ {char const* url; int /*<<< orphan*/  rev; } ;
typedef  TYPE_2__ svn_client__pathrev_t ;
struct TYPE_23__ {char* path; void* rev; int /*<<< orphan*/ * pool; int /*<<< orphan*/  is_first; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ copyfrom_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_MISSING_URL ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_ERR_RA_DAV_REQUEST_FAILED ; 
 void* SVN_INVALID_REVNUM ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  copyfrom_info_receiver ; 
 TYPE_1__* svn_client__ensure_ra_session_url (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_2__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client__resolve_rev_and_url (TYPE_2__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client_url_from_path2 (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_ra_get_location_segments (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_copy_source(const char **original_repos_relpath,
                            svn_revnum_t *original_revision,
                            const char *path_or_url,
                            const svn_opt_revision_t *revision,
                            svn_ra_session_t *ra_session,
                            svn_client_ctx_t *ctx,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  copyfrom_info_t copyfrom_info = { 0 };
  apr_pool_t *sesspool = svn_pool_create(scratch_pool);
  svn_client__pathrev_t *at_loc;
  const char *old_session_url = NULL;

  copyfrom_info.is_first = TRUE;
  copyfrom_info.path = NULL;
  copyfrom_info.rev = SVN_INVALID_REVNUM;
  copyfrom_info.pool = result_pool;

  if (!ra_session)
    {
      SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &at_loc,
                                                path_or_url, NULL,
                                                revision, revision,
                                                ctx, sesspool));
    }
  else
    {
      const char *url;
      if (svn_path_is_url(path_or_url))
        url = path_or_url;
      else
        {
          SVN_ERR(svn_client_url_from_path2(&url, path_or_url, ctx, sesspool,
                                            sesspool));

          if (! url)
            return svn_error_createf(SVN_ERR_ENTRY_MISSING_URL, NULL,
                                     _("'%s' has no URL"), path_or_url);
        }

      SVN_ERR(svn_client__ensure_ra_session_url(&old_session_url, ra_session,
                                                url, sesspool));

      err = svn_client__resolve_rev_and_url(&at_loc, ra_session, path_or_url,
                                            revision, revision, ctx,
                                            sesspool);

      /* On error reparent back (and return), otherwise reparent to new
         location */
      SVN_ERR(svn_error_compose_create(
                err,
                svn_ra_reparent(ra_session, err ? old_session_url
                                                : at_loc->url, sesspool)));
    }

  /* Find the copy source.  Walk the location segments to find the revision
     at which this node was created (copied or added). */

  err = svn_ra_get_location_segments(ra_session, "", at_loc->rev, at_loc->rev,
                                     SVN_INVALID_REVNUM,
                                     copyfrom_info_receiver, &copyfrom_info,
                                     scratch_pool);

  if (old_session_url)
    err = svn_error_compose_create(
                    err,
                    svn_ra_reparent(ra_session, old_session_url, sesspool));

  svn_pool_destroy(sesspool);

  if (err)
    {
      if (err->apr_err == SVN_ERR_FS_NOT_FOUND ||
          err->apr_err == SVN_ERR_RA_DAV_REQUEST_FAILED)
        {
          /* A locally-added but uncommitted versioned resource won't
             exist in the repository. */
            svn_error_clear(err);
            err = SVN_NO_ERROR;

            *original_repos_relpath = NULL;
            *original_revision = SVN_INVALID_REVNUM;
        }
      return svn_error_trace(err);
    }

  *original_repos_relpath = copyfrom_info.path;
  *original_revision = copyfrom_info.rev;
  return SVN_NO_ERROR;
}
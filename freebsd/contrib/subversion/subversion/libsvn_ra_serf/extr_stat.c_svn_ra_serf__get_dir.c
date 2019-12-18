#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_13__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
struct TYPE_12__ {char* path; } ;
struct TYPE_14__ {scalar_t__ supports_deadprop_count; TYPE_1__ session_url; } ;
typedef  TYPE_3__ svn_ra_serf__session_t ;
struct TYPE_15__ {int /*<<< orphan*/  done; } ;
typedef  TYPE_4__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct get_dir_baton_t {scalar_t__ supports_deadprop_count; char const* path; int /*<<< orphan*/ * dirents; int /*<<< orphan*/ * ret_props; int /*<<< orphan*/  is_directory; int /*<<< orphan*/ * result_pool; } ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVN_DIRENT_HAS_PROPS ; 
 int SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  all_props ; 
 int /*<<< orphan*/  apr_hash_clear (int /*<<< orphan*/ *) ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dir_dirents_cb ; 
 int /*<<< orphan*/  get_dir_props_cb ; 
 int /*<<< orphan*/  get_dirent_props (int,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_wait (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__create_propfind_handler (TYPE_4__**,TYPE_3__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct get_dir_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__get_stable_url (char const**,int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_create (TYPE_4__*) ; 
 scalar_t__ svn_tristate_false ; 
 scalar_t__ svn_tristate_unknown ; 

svn_error_t *
svn_ra_serf__get_dir(svn_ra_session_t *ra_session,
                     apr_hash_t **dirents,
                     svn_revnum_t *fetched_rev,
                     apr_hash_t **ret_props,
                     const char *rel_path,
                     svn_revnum_t revision,
                     apr_uint32_t dirent_fields,
                     apr_pool_t *result_pool)
{
  svn_ra_serf__session_t *session = ra_session->priv;
  apr_pool_t *scratch_pool = svn_pool_create(result_pool);
  svn_ra_serf__handler_t *dirent_handler = NULL;
  svn_ra_serf__handler_t *props_handler = NULL;
  const char *path;
  struct get_dir_baton_t gdb;
  svn_error_t *err = SVN_NO_ERROR;

  gdb.result_pool = result_pool;
  gdb.is_directory = FALSE;
  gdb.supports_deadprop_count = svn_tristate_unknown;

  path = session->session_url.path;

  /* If we have a relative path, URI encode and append it. */
  if (rel_path)
    {
      path = svn_path_url_add_component2(path, rel_path, scratch_pool);
    }

  /* If the user specified a peg revision other than HEAD, we have to fetch
     the baseline collection url for that revision. If not, we can use the
     public url. */
  if (SVN_IS_VALID_REVNUM(revision) || fetched_rev)
    {
      SVN_ERR(svn_ra_serf__get_stable_url(&path, fetched_rev,
                                          session,
                                          path, revision,
                                          scratch_pool, scratch_pool));
      revision = SVN_INVALID_REVNUM;
    }
  /* REVISION is always SVN_INVALID_REVNUM  */
  SVN_ERR_ASSERT(!SVN_IS_VALID_REVNUM(revision));

  gdb.path = path;

  /* If we're asked for children, fetch them now. */
  if (dirents)
    {
      /* Always request node kind to check that path is really a
       * directory. */
      if (!ret_props)
        dirent_fields |= SVN_DIRENT_KIND;

      gdb.dirents = apr_hash_make(result_pool);

      SVN_ERR(svn_ra_serf__create_propfind_handler(
                                          &dirent_handler, session,
                                          path, SVN_INVALID_REVNUM, "1",
                                          get_dirent_props(dirent_fields,
                                                           session,
                                                           scratch_pool),
                                          get_dir_dirents_cb, &gdb,
                                          scratch_pool));

      svn_ra_serf__request_create(dirent_handler);
    }
  else
    gdb.dirents = NULL;

  if (ret_props)
    {
      gdb.ret_props = apr_hash_make(result_pool);
      SVN_ERR(svn_ra_serf__create_propfind_handler(
                                          &props_handler, session,
                                          path, SVN_INVALID_REVNUM, "0",
                                          all_props,
                                          get_dir_props_cb, &gdb,
                                          scratch_pool));

      svn_ra_serf__request_create(props_handler);
    }
  else
    gdb.ret_props = NULL;

  if (dirent_handler)
    {
      err = svn_error_trace(
              svn_ra_serf__context_run_wait(&dirent_handler->done,
                                            session,
                                            scratch_pool));

      if (err)
        {
          svn_pool_clear(scratch_pool); /* Unregisters outstanding requests */
          return err;
        }

      if (gdb.supports_deadprop_count == svn_tristate_false
          && session->supports_deadprop_count == svn_tristate_unknown
          && dirent_fields & SVN_DIRENT_HAS_PROPS)
        {
          /* We have to requery as the server didn't give us the right
             information */
          session->supports_deadprop_count = svn_tristate_false;

          apr_hash_clear(gdb.dirents);

          SVN_ERR(svn_ra_serf__create_propfind_handler(
                                              &dirent_handler, session,
                                              path, SVN_INVALID_REVNUM, "1",
                                              get_dirent_props(dirent_fields,
                                                               session,
                                                               scratch_pool),
                                              get_dir_dirents_cb, &gdb,
                                              scratch_pool));

          svn_ra_serf__request_create(dirent_handler);
        }
    }

  if (props_handler)
    {
      err = svn_error_trace(
              svn_ra_serf__context_run_wait(&props_handler->done,
                                            session,
                                            scratch_pool));
    }

  /* And dirent again for the case when we had to send the request again */
  if (! err && dirent_handler)
    {
      err = svn_error_trace(
              svn_ra_serf__context_run_wait(&dirent_handler->done,
                                            session,
                                            scratch_pool));
    }

  if (!err && gdb.supports_deadprop_count != svn_tristate_unknown)
    session->supports_deadprop_count = gdb.supports_deadprop_count;

  svn_pool_destroy(scratch_pool); /* Unregisters outstanding requests */

  SVN_ERR(err);

  if (!gdb.is_directory)
    return svn_error_create(SVN_ERR_FS_NOT_DIRECTORY, NULL,
                            _("Can't get entries of non-directory"));

  if (ret_props)
    *ret_props = gdb.ret_props;

  if (dirents)
    *dirents = gdb.dirents;

  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {void* client_receiver_baton; int /*<<< orphan*/  (* client_receiver_func ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ wc_info_receiver_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_31__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_32__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct TYPE_33__ {scalar_t__ kind; } ;
typedef  TYPE_4__ svn_dirent_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  (* svn_client_info_receiver2_t ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_client_info2_t ;
struct TYPE_34__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_5__ svn_client_ctx_t ;
struct TYPE_35__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_6__ svn_client__pathrev_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ SVN_DEPTH_IS_RECURSIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 scalar_t__ SVN_ERR_RA_NOT_IMPLEMENTED ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_info_from_dirent (int /*<<< orphan*/ **,TYPE_4__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_external_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  (*) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_dir_info (int /*<<< orphan*/ *,TYPE_6__*,char*,int /*<<< orphan*/  (*) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  same_resource_in_head (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_6__**,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 TYPE_3__* svn_ra_get_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_get_locks2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_stat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_4__**,int /*<<< orphan*/ *) ; 
 char* svn_uri_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__externals_defined_below (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_info (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_info_receiver ; 

svn_error_t *
svn_client_info4(const char *abspath_or_url,
                 const svn_opt_revision_t *peg_revision,
                 const svn_opt_revision_t *revision,
                 svn_depth_t depth,
                 svn_boolean_t fetch_excluded,
                 svn_boolean_t fetch_actual_only,
                 svn_boolean_t include_externals,
                 const apr_array_header_t *changelists,
                 svn_client_info_receiver2_t receiver,
                 void *receiver_baton,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *pool)
{
  svn_ra_session_t *ra_session;
  svn_client__pathrev_t *pathrev;
  svn_lock_t *lock;
  svn_boolean_t related;
  const char *base_name;
  svn_dirent_t *the_ent;
  svn_client_info2_t *info;
  svn_error_t *err;

  if (depth == svn_depth_unknown)
    depth = svn_depth_empty;

  if ((revision == NULL
       || revision->kind == svn_opt_revision_unspecified)
      && (peg_revision == NULL
          || peg_revision->kind == svn_opt_revision_unspecified))
    {
      /* Do all digging in the working copy. */
      wc_info_receiver_baton_t b;

      b.client_receiver_func = receiver;
      b.client_receiver_baton = receiver_baton;
      SVN_ERR(svn_wc__get_info(ctx->wc_ctx, abspath_or_url, depth,
                               fetch_excluded, fetch_actual_only, changelists,
                               wc_info_receiver, &b,
                               ctx->cancel_func, ctx->cancel_baton, pool));

      if (include_externals && SVN_DEPTH_IS_RECURSIVE(depth))
        {
          apr_hash_t *external_map;

          SVN_ERR(svn_wc__externals_defined_below(&external_map,
                                                  ctx->wc_ctx, abspath_or_url,
                                                  pool, pool));

          SVN_ERR(do_external_info(external_map,
                                   depth, fetch_excluded, fetch_actual_only,
                                   changelists,
                                   receiver, receiver_baton, ctx, pool));
        }

      return SVN_NO_ERROR;
    }

  /* Go repository digging instead. */

  /* Trace rename history (starting at path_or_url@peg_revision) and
     return RA session to the possibly-renamed URL as it exists in REVISION.
     The ra_session returned will be anchored on this "final" URL. */
  SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &pathrev,
                                            abspath_or_url, NULL, peg_revision,
                                            revision, ctx, pool));
  base_name = svn_uri_basename(pathrev->url, pool);

  /* Get the dirent for the URL itself. */
  SVN_ERR(svn_ra_stat(ra_session, "", pathrev->rev, &the_ent, pool));

  if (! the_ent)
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             _("URL '%s' non-existent in revision %ld"),
                             pathrev->url, pathrev->rev);

  /* Check if the URL exists in HEAD and refers to the same resource.
     In this case, we check the repository for a lock on this URL.

     ### There is a possible race here, since HEAD might have changed since
     ### we checked it.  A solution to this problem could be to do the below
     ### check in a loop which only terminates if the HEAD revision is the same
     ### before and after this check.  That could, however, lead to a
     ### starvation situation instead.  */
  SVN_ERR(same_resource_in_head(&related, pathrev->url, pathrev->rev,
                                ra_session, ctx, pool));
  if (related)
    {
      err = svn_ra_get_lock(ra_session, &lock, "", pool);

      /* An old mod_dav_svn will always work; there's nothing wrong with
         doing a PROPFIND for a property named "DAV:supportedlock". But
         an old svnserve will error. */
      if (err && err->apr_err == SVN_ERR_RA_NOT_IMPLEMENTED)
        {
          svn_error_clear(err);
          lock = NULL;
        }
      else if (err)
        return svn_error_trace(err);
    }
  else
    lock = NULL;

  /* Push the URL's dirent (and lock) at the callback.*/
  SVN_ERR(build_info_from_dirent(&info, the_ent, lock, pathrev, pool));
  SVN_ERR(receiver(receiver_baton, base_name, info, pool));

  /* Possibly recurse, using the original RA session. */
  if (depth > svn_depth_empty && (the_ent->kind == svn_node_dir))
    {
      apr_hash_t *locks;

      if (peg_revision->kind == svn_opt_revision_head)
        {
          err = svn_ra_get_locks2(ra_session, &locks, "", depth,
                                  pool);

          /* Catch specific errors thrown by old mod_dav_svn or svnserve. */
          if (err && err->apr_err == SVN_ERR_RA_NOT_IMPLEMENTED)
            {
              svn_error_clear(err);
              locks = apr_hash_make(pool); /* use an empty hash */
            }
          else if (err)
            return svn_error_trace(err);
        }
      else
        locks = apr_hash_make(pool); /* use an empty hash */

      SVN_ERR(push_dir_info(ra_session, pathrev, "",
                            receiver, receiver_baton,
                            depth, ctx, locks, pool));
    }

  return SVN_NO_ERROR;
}
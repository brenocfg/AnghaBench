#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_6__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct recursive_propget_receiver_baton {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * props; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_7__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recursive_propget_receiver ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/  svn_wc__prop_list_recursive (int /*<<< orphan*/ ,char const*,char const*,scalar_t__,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ,struct recursive_propget_receiver_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__prop_retrieve_recursive (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_prop_from_wc(apr_hash_t **props,
                 const char *propname,
                 const char *target_abspath,
                 svn_boolean_t pristine,
                 svn_node_kind_t kind,
                 svn_depth_t depth,
                 const apr_array_header_t *changelists,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  struct recursive_propget_receiver_baton rb;

  /* Technically, svn_depth_unknown just means use whatever depth(s)
     we find in the working copy.  But this is a walk over extant
     working copy paths: if they're there at all, then by definition
     the local depth reaches them, so let's just use svn_depth_infinity
     to get there. */
  if (depth == svn_depth_unknown)
    depth = svn_depth_infinity;

  if (!pristine && depth == svn_depth_infinity
      && (!changelists || changelists->nelts == 0))
    {
      /* Handle this common svn:mergeinfo case more efficient than the target
         list handling in the recursive retrieval. */
      SVN_ERR(svn_wc__prop_retrieve_recursive(
                            props, ctx->wc_ctx, target_abspath, propname,
                            result_pool, scratch_pool));
      return SVN_NO_ERROR;
    }

  *props = apr_hash_make(result_pool);
  rb.props = *props;
  rb.pool = result_pool;
  rb.wc_ctx = ctx->wc_ctx;

  SVN_ERR(svn_wc__prop_list_recursive(ctx->wc_ctx, target_abspath,
                                      propname, depth, pristine,
                                      changelists,
                                      recursive_propget_receiver, &rb,
                                      ctx->cancel_func, ctx->cancel_baton,
                                      scratch_pool));

  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  (* svn_wc__proplist_receiver_t ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct propname_filter_baton_t {char const* propname; void* receiver_baton; int /*<<< orphan*/  (* receiver_func ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_8__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/  (*) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propname_filter_receiver (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_depth_empty 131 
#define  svn_depth_files 130 
#define  svn_depth_immediates 129 
#define  svn_depth_infinity 128 
 int /*<<< orphan*/  svn_hash_from_cstring_keys (int /*<<< orphan*/ **,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props_streamily (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/  (*) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_changelist_match (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__prop_list_recursive(svn_wc_context_t *wc_ctx,
                            const char *local_abspath,
                            const char *propname,
                            svn_depth_t depth,
                            svn_boolean_t pristine,
                            const apr_array_header_t *changelists,
                            svn_wc__proplist_receiver_t receiver_func,
                            void *receiver_baton,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *scratch_pool)
{
  svn_wc__proplist_receiver_t receiver = receiver_func;
  void *baton = receiver_baton;
  struct propname_filter_baton_t pfb;

  pfb.receiver_func = receiver_func;
  pfb.receiver_baton = receiver_baton;
  pfb.propname = propname;

  SVN_ERR_ASSERT(receiver_func);

  if (propname)
    {
      baton = &pfb;
      receiver = propname_filter_receiver;
    }

  switch (depth)
    {
    case svn_depth_empty:
      {
        apr_hash_t *props;
        apr_hash_t *changelist_hash = NULL;

        if (changelists && changelists->nelts)
          SVN_ERR(svn_hash_from_cstring_keys(&changelist_hash,
                                             changelists, scratch_pool));

        if (!svn_wc__internal_changelist_match(wc_ctx->db, local_abspath,
                                               changelist_hash, scratch_pool))
          break;

        if (pristine)
          SVN_ERR(svn_wc__db_read_pristine_props(&props, wc_ctx->db,
                                                 local_abspath,
                                                 scratch_pool, scratch_pool));
        else
          SVN_ERR(svn_wc__db_read_props(&props, wc_ctx->db, local_abspath,
                                        scratch_pool, scratch_pool));

        if (props && apr_hash_count(props) > 0)
          SVN_ERR(receiver(baton, local_abspath, props, scratch_pool));
      }
      break;
    case svn_depth_files:
    case svn_depth_immediates:
    case svn_depth_infinity:
      {
        SVN_ERR(svn_wc__db_read_props_streamily(wc_ctx->db, local_abspath,
                                                depth, pristine,
                                                changelists, receiver, baton,
                                                cancel_func, cancel_baton,
                                                scratch_pool));
      }
      break;
    default:
      SVN_ERR_MALFUNCTION();
    }

  return SVN_NO_ERROR;
}
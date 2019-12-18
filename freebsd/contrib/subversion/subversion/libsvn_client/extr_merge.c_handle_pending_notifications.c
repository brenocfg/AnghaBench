#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct merge_dir_baton_t {int /*<<< orphan*/ * pending_deletes; } ;
struct TYPE_9__ {TYPE_1__* ctx; } ;
typedef  TYPE_3__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_7__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_kind_from_word (int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_delete ; 

__attribute__((used)) static svn_error_t *
handle_pending_notifications(merge_cmd_baton_t *merge_b,
                             struct merge_dir_baton_t *db,
                             apr_pool_t *scratch_pool)
{
  if (merge_b->ctx->notify_func2 && db->pending_deletes)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, db->pending_deletes);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *del_abspath = apr_hash_this_key(hi);
          svn_wc_notify_t *notify;

          notify = svn_wc_create_notify(del_abspath,
                                        svn_wc_notify_update_delete,
                                        scratch_pool);
          notify->kind = svn_node_kind_from_word(
                                    apr_hash_this_val(hi));

          merge_b->ctx->notify_func2(merge_b->ctx->notify_baton2,
                                     notify, scratch_pool);
        }

      db->pending_deletes = NULL;
    }
  return SVN_NO_ERROR;
}
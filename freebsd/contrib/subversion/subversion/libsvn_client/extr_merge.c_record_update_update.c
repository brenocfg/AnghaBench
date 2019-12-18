#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* prop_state; void* content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ svn_wc_notify_t ;
typedef  void* svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {scalar_t__ ancestral; } ;
struct TYPE_12__ {TYPE_1__* ctx; int /*<<< orphan*/  merged_abspaths; scalar_t__ reintegrate_merge; TYPE_2__ merge_source; } ;
typedef  TYPE_4__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  notify_merge_begin (TYPE_4__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_path (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_update ; 

__attribute__((used)) static svn_error_t *
record_update_update(merge_cmd_baton_t *merge_b,
                     const char *local_abspath,
                     svn_node_kind_t kind,
                     svn_wc_notify_state_t content_state,
                     svn_wc_notify_state_t prop_state,
                     apr_pool_t *scratch_pool)
{
  if (merge_b->merge_source.ancestral || merge_b->reintegrate_merge)
    {
      store_path(merge_b->merged_abspaths, local_abspath);
    }

  if (merge_b->ctx->notify_func2)
    {
      svn_wc_notify_t *notify;

      SVN_ERR(notify_merge_begin(merge_b, local_abspath, FALSE, scratch_pool));

      notify = svn_wc_create_notify(local_abspath, svn_wc_notify_update_update,
                                    scratch_pool);
      notify->kind = kind;
      notify->content_state = content_state;
      notify->prop_state = prop_state;

      merge_b->ctx->notify_func2(merge_b->ctx->notify_baton2, notify,
                                 scratch_pool);
    }

  return SVN_NO_ERROR;
}
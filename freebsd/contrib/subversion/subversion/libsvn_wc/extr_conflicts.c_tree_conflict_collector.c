#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ action; scalar_t__ prop_state; scalar_t__ content_state; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
struct conflict_status_walker_baton {scalar_t__ resolve_later; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_pool_get (scalar_t__) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_gets (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,char const*) ; 
 scalar_t__ svn_wc_notify_state_conflicted ; 
 scalar_t__ svn_wc_notify_tree_conflict ; 

__attribute__((used)) static void
tree_conflict_collector(void *baton,
                        const svn_wc_notify_t *notify,
                        apr_pool_t *pool)
{
  struct conflict_status_walker_baton *cswb = baton;

  if (cswb->notify_func)
    cswb->notify_func(cswb->notify_baton, notify, pool);

  if (cswb->resolve_later
      && (notify->action == svn_wc_notify_tree_conflict
          || notify->prop_state == svn_wc_notify_state_conflicted
          || notify->content_state == svn_wc_notify_state_conflicted))
    {
      if (!svn_hash_gets(cswb->resolve_later, notify->path))
        {
          const char *dup_path;

          dup_path = apr_pstrdup(apr_hash_pool_get(cswb->resolve_later),
                                 notify->path);

          svn_hash_sets(cswb->resolve_later, dup_path, dup_path);
        }
    }
}
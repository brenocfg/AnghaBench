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
struct TYPE_4__ {char const* path; void* old_revision; void* revision; int /*<<< orphan*/  lock_state; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  kind; int /*<<< orphan*/  action; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_action_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* SVN_INVALID_REVNUM ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_wc_notify_lock_state_unknown ; 
 int /*<<< orphan*/  svn_wc_notify_state_unknown ; 

svn_wc_notify_t *
svn_wc_create_notify(const char *path,
                     svn_wc_notify_action_t action,
                     apr_pool_t *pool)
{
  svn_wc_notify_t *ret = apr_pcalloc(pool, sizeof(*ret));
  ret->path = path;
  ret->action = action;
  ret->kind = svn_node_unknown;
  ret->content_state = ret->prop_state = svn_wc_notify_state_unknown;
  ret->lock_state = svn_wc_notify_lock_state_unknown;
  ret->revision = SVN_INVALID_REVNUM;
  ret->old_revision = SVN_INVALID_REVNUM;

  return ret;
}
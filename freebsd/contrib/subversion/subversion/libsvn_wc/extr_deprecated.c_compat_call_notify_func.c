#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  mime_type; int /*<<< orphan*/  kind; int /*<<< orphan*/  action; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
struct compat_notify_baton_t {int /*<<< orphan*/  baton; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compat_call_notify_func(void *baton,
                        const svn_wc_notify_t *n,
                        apr_pool_t *pool)
{
  struct compat_notify_baton_t *nb = baton;

  if (nb->func)
    (*nb->func)(nb->baton, n->path, n->action, n->kind, n->mime_type,
                n->content_state, n->prop_state, n->revision);
}
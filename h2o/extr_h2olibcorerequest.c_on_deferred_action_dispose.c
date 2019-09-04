#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_deferred_request_action_t {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_deferred_action_dispose(void *_action)
{
    struct st_deferred_request_action_t *action = _action;
    h2o_timer_unlink(&action->timeout);
}
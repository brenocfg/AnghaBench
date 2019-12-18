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
struct mdesc_notifier_client {int /*<<< orphan*/  add; int /*<<< orphan*/  node_name; int /*<<< orphan*/  remove; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  invoke_on_missing (int /*<<< orphan*/ ,struct mdesc_handle*,struct mdesc_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void notify_one(struct mdesc_notifier_client *p,
		       struct mdesc_handle *old_hp,
		       struct mdesc_handle *new_hp)
{
	invoke_on_missing(p->node_name, old_hp, new_hp, p->remove);
	invoke_on_missing(p->node_name, new_hp, old_hp, p->add);
}
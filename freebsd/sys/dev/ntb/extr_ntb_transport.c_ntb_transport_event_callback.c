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
struct ntb_transport_ctx {int /*<<< orphan*/  link_cleanup; int /*<<< orphan*/  link_work; int /*<<< orphan*/  link_width; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ntb_transport_ctx*) ; 
 scalar_t__ ntb_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_printf (int,char*) ; 
 int /*<<< orphan*/  ntb_transport_link_work ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
ntb_transport_event_callback(void *data)
{
	struct ntb_transport_ctx *nt = data;

	if (ntb_link_is_up(nt->dev, &nt->link_speed, &nt->link_width)) {
		ntb_printf(1, "HW link up\n");
		callout_reset(&nt->link_work, 0, ntb_transport_link_work, nt);
	} else {
		ntb_printf(1, "HW link down\n");
		taskqueue_enqueue(taskqueue_swi, &nt->link_cleanup);
	}
}
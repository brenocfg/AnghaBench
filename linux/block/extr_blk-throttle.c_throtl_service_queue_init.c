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
struct throtl_service_queue {int /*<<< orphan*/  pending_timer; int /*<<< orphan*/  pending_tree; int /*<<< orphan*/ * queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  throtl_pending_timer_fn ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void throtl_service_queue_init(struct throtl_service_queue *sq)
{
	INIT_LIST_HEAD(&sq->queued[0]);
	INIT_LIST_HEAD(&sq->queued[1]);
	sq->pending_tree = RB_ROOT_CACHED;
	timer_setup(&sq->pending_timer, throtl_pending_timer_fn, 0);
}
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
struct bnxt_cp_ring {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_CP_DISABLE_DB (int /*<<< orphan*/ *) ; 
 int FILTER_SCHEDULE_THREAD ; 

__attribute__((used)) static int
bnxt_handle_rx_cp(void *arg)
{
	struct bnxt_cp_ring *cpr = arg;

	/* Disable further interrupts for this queue */
	BNXT_CP_DISABLE_DB(&cpr->ring);
	return FILTER_SCHEDULE_THREAD;
}
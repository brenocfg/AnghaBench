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
struct ieee80211com {int /*<<< orphan*/  ic_restart_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void
ieee80211_restart_all(struct ieee80211com *ic)
{
	/*
	 * NB: do not use ieee80211_runtask here, we will
	 * block & drain net80211 taskqueue.
	 */
	taskqueue_enqueue(taskqueue_thread, &ic->ic_restart_task);
}
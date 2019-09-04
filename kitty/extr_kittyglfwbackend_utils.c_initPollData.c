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
typedef  int /*<<< orphan*/  EventLoopData ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  addWatch (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drain_wakeup_fd ; 

void
initPollData(EventLoopData *eld, int wakeup_fd, int display_fd) {
    addWatch(eld, "display", display_fd, POLLIN, 1, NULL, NULL);
    addWatch(eld, "wakeup", wakeup_fd, POLLIN, 1, drain_wakeup_fd, NULL);
}
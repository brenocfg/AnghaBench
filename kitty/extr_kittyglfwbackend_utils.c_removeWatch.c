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
typedef  int /*<<< orphan*/  id_type ;
typedef  int /*<<< orphan*/  EventLoopData ;

/* Variables and functions */
 int /*<<< orphan*/  removeX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_fds ; 
 int /*<<< orphan*/  watches ; 

void
removeWatch(EventLoopData *eld, id_type watch_id) {
    removeX(watches, watch_id, update_fds);
}
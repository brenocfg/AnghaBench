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
typedef  int /*<<< orphan*/  i3bar_child ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  child ; 
 int /*<<< orphan*/ * child_sig ; 
 int /*<<< orphan*/  ev_child_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stdin_io ; 

__attribute__((used)) static void cleanup(void) {
    if (stdin_io != NULL) {
        ev_io_stop(main_loop, stdin_io);
        FREE(stdin_io);
    }

    if (child_sig != NULL) {
        ev_child_stop(main_loop, child_sig);
        FREE(child_sig);
    }

    memset(&child, 0, sizeof(i3bar_child));
}
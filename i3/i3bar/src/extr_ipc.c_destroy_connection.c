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
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_stop (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* i3_connection ; 
 int /*<<< orphan*/  main_loop ; 

void destroy_connection(void) {
    close(i3_connection->fd);
    ev_io_stop(main_loop, i3_connection);
}
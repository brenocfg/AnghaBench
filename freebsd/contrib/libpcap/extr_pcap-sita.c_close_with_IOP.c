#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; int find_fd; } ;

/* Variables and functions */
 int LIVE ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__** units ; 

__attribute__((used)) static void close_with_IOP(int chassis, int geoslot, int flag) {
	int		*id;

	if (flag == LIVE)	id = &units[chassis][geoslot].fd;
	else				id = &units[chassis][geoslot].find_fd;

	if (*id) {										/* this was the last time, so... if we are connected... */
		close(*id);									/* disconnect us */
		*id = 0;									/* and forget that the descriptor exists because we are not open */
	}
}
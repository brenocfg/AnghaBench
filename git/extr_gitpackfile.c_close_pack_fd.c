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
struct packed_git {int pack_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pack_open_fds ; 

int close_pack_fd(struct packed_git *p)
{
	if (p->pack_fd < 0)
		return 0;

	close(p->pack_fd);
	pack_open_fds--;
	p->pack_fd = -1;

	return 1;
}
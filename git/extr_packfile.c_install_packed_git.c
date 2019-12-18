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
struct repository {TYPE_1__* objects; } ;
struct packed_git {int pack_fd; struct packed_git* next; } ;
struct TYPE_2__ {struct packed_git* packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  pack_open_fds ; 

void install_packed_git(struct repository *r, struct packed_git *pack)
{
	if (pack->pack_fd != -1)
		pack_open_fds++;

	pack->next = r->objects->packed_git;
	r->objects->packed_git = pack;
}
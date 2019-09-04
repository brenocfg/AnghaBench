#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct packed_git {int pack_fd; struct packed_git* next; } ;
struct pack_window {int dummy; } ;
struct TYPE_4__ {TYPE_1__* objects; } ;
struct TYPE_3__ {struct packed_git* packed_git; } ;

/* Variables and functions */
 int close_pack_fd (struct packed_git*) ; 
 int /*<<< orphan*/  find_lru_pack (struct packed_git*,struct packed_git**,struct pack_window**,int*) ; 
 TYPE_2__* the_repository ; 

__attribute__((used)) static int close_one_pack(void)
{
	struct packed_git *p, *lru_p = NULL;
	struct pack_window *mru_w = NULL;
	int accept_windows_inuse = 1;

	for (p = the_repository->objects->packed_git; p; p = p->next) {
		if (p->pack_fd == -1)
			continue;
		find_lru_pack(p, &lru_p, &mru_w, &accept_windows_inuse);
	}

	if (lru_p)
		return close_pack_fd(lru_p);

	return 0;
}
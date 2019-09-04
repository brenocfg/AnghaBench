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
struct packed_git {int /*<<< orphan*/  windows; struct packed_git* next; } ;
struct pack_window {int /*<<< orphan*/  next; scalar_t__ len; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__* objects; } ;
struct TYPE_3__ {struct packed_git* packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pack_window*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pack_mapped ; 
 int /*<<< orphan*/  pack_open_windows ; 
 int /*<<< orphan*/  scan_windows (struct packed_git*,struct packed_git**,struct pack_window**,struct pack_window**) ; 
 TYPE_2__* the_repository ; 

__attribute__((used)) static int unuse_one_window(struct packed_git *current)
{
	struct packed_git *p, *lru_p = NULL;
	struct pack_window *lru_w = NULL, *lru_l = NULL;

	if (current)
		scan_windows(current, &lru_p, &lru_w, &lru_l);
	for (p = the_repository->objects->packed_git; p; p = p->next)
		scan_windows(p, &lru_p, &lru_w, &lru_l);
	if (lru_p) {
		munmap(lru_w->base, lru_w->len);
		pack_mapped -= lru_w->len;
		if (lru_l)
			lru_l->next = lru_w->next;
		else
			lru_p->windows = lru_w->next;
		free(lru_w);
		pack_open_windows--;
		return 1;
	}
	return 0;
}
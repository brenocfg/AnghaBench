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
struct packed_git {struct pack_window* windows; int /*<<< orphan*/  pack_name; } ;
struct pack_window {struct pack_window* next; scalar_t__ len; int /*<<< orphan*/  base; scalar_t__ inuse_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pack_window*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pack_mapped ; 
 int /*<<< orphan*/  pack_open_windows ; 

void close_pack_windows(struct packed_git *p)
{
	while (p->windows) {
		struct pack_window *w = p->windows;

		if (w->inuse_cnt)
			die("pack '%s' still has open windows to it",
			    p->pack_name);
		munmap(w->base, w->len);
		pack_mapped -= w->len;
		pack_open_windows--;
		p->windows = w->next;
		free(w);
	}
}
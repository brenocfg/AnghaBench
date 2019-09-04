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
struct packed_git {scalar_t__ mtime; struct pack_window* windows; } ;
struct pack_window {scalar_t__ last_used; scalar_t__ inuse_cnt; struct pack_window* next; } ;

/* Variables and functions */

__attribute__((used)) static void find_lru_pack(struct packed_git *p, struct packed_git **lru_p, struct pack_window **mru_w, int *accept_windows_inuse)
{
	struct pack_window *w, *this_mru_w;
	int has_windows_inuse = 0;

	/*
	 * Reject this pack if it has windows and the previously selected
	 * one does not.  If this pack does not have windows, reject
	 * it if the pack file is newer than the previously selected one.
	 */
	if (*lru_p && !*mru_w && (p->windows || p->mtime > (*lru_p)->mtime))
		return;

	for (w = this_mru_w = p->windows; w; w = w->next) {
		/*
		 * Reject this pack if any of its windows are in use,
		 * but the previously selected pack did not have any
		 * inuse windows.  Otherwise, record that this pack
		 * has windows in use.
		 */
		if (w->inuse_cnt) {
			if (*accept_windows_inuse)
				has_windows_inuse = 1;
			else
				return;
		}

		if (w->last_used > this_mru_w->last_used)
			this_mru_w = w;

		/*
		 * Reject this pack if it has windows that have been
		 * used more recently than the previously selected pack.
		 * If the previously selected pack had windows inuse and
		 * we have not encountered a window in this pack that is
		 * inuse, skip this check since we prefer a pack with no
		 * inuse windows to one that has inuse windows.
		 */
		if (*mru_w && *accept_windows_inuse == has_windows_inuse &&
		    this_mru_w->last_used > (*mru_w)->last_used)
			return;
	}

	/*
	 * Select this pack.
	 */
	*mru_w = this_mru_w;
	*lru_p = p;
	*accept_windows_inuse = has_windows_inuse;
}
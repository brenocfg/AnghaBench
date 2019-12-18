#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* windows; } ;
typedef  TYPE_1__ git_mwindow_file ;
struct TYPE_7__ {scalar_t__ last_used; int /*<<< orphan*/  inuse_cnt; struct TYPE_7__* next; } ;
typedef  TYPE_2__ git_mwindow ;

/* Variables and functions */

__attribute__((used)) static void git_mwindow_scan_lru(
	git_mwindow_file *mwf,
	git_mwindow **lru_w,
	git_mwindow **lru_l)
{
	git_mwindow *w, *w_l;

	for (w_l = NULL, w = mwf->windows; w; w = w->next) {
		if (!w->inuse_cnt) {
			/*
			 * If the current one is more recent than the last one,
			 * store it in the output parameter. If lru_w is NULL,
			 * it's the first loop, so store it as well.
			 */
			if (!*lru_w || w->last_used < (*lru_w)->last_used) {
				*lru_w = w;
				*lru_l = w_l;
			}
		}
		w_l = w;
	}
}
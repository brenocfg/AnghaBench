#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* windows; } ;
typedef  TYPE_1__ git_mwindow_file ;
struct TYPE_16__ {size_t length; int /*<<< orphan*/ * contents; } ;
struct TYPE_14__ {int /*<<< orphan*/  open_windows; int /*<<< orphan*/  mapped; TYPE_5__ windowfiles; } ;
typedef  TYPE_2__ git_mwindow_ctl ;
struct TYPE_12__ {scalar_t__ len; } ;
struct TYPE_15__ {scalar_t__ inuse_cnt; struct TYPE_15__* next; TYPE_10__ window_map; } ;
typedef  TYPE_3__ git_mwindow ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_futils_mmap_free (TYPE_10__*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_5__*) ; 
 TYPE_1__* git_vector_get (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  git_vector_remove (TYPE_5__*,size_t) ; 
 TYPE_2__ mem_ctl ; 

void git_mwindow_free_all_locked(git_mwindow_file *mwf)
{
	git_mwindow_ctl *ctl = &mem_ctl;
	size_t i;

	/*
	 * Remove these windows from the global list
	 */
	for (i = 0; i < ctl->windowfiles.length; ++i){
		if (git_vector_get(&ctl->windowfiles, i) == mwf) {
			git_vector_remove(&ctl->windowfiles, i);
			break;
		}
	}

	if (ctl->windowfiles.length == 0) {
		git_vector_free(&ctl->windowfiles);
		ctl->windowfiles.contents = NULL;
	}

	while (mwf->windows) {
		git_mwindow *w = mwf->windows;
		assert(w->inuse_cnt == 0);

		ctl->mapped -= w->window_map.len;
		ctl->open_windows--;

		git_futils_mmap_free(&w->window_map);

		mwf->windows = w->next;
		git__free(w);
	}
}
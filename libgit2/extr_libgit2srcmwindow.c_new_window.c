#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t git_off_t ;
typedef  int /*<<< orphan*/  git_mwindow_file ;
struct TYPE_8__ {scalar_t__ mapped; scalar_t__ open_windows; scalar_t__ peak_mapped; scalar_t__ peak_open_windows; int /*<<< orphan*/  mmap_calls; } ;
typedef  TYPE_1__ git_mwindow_ctl ;
struct TYPE_9__ {size_t offset; int /*<<< orphan*/  window_map; } ;
typedef  TYPE_2__ git_mwindow ;
typedef  int /*<<< orphan*/  git_file ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 TYPE_2__* git__malloc (int) ; 
 scalar_t__ git_futils_mmap_ro (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t) ; 
 scalar_t__ git_mwindow__mapped_limit ; 
 int git_mwindow__window_size ; 
 scalar_t__ git_mwindow_close_lru (int /*<<< orphan*/ *) ; 
 TYPE_1__ mem_ctl ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 

__attribute__((used)) static git_mwindow *new_window(
	git_mwindow_file *mwf,
	git_file fd,
	git_off_t size,
	git_off_t offset)
{
	git_mwindow_ctl *ctl = &mem_ctl;
	size_t walign = git_mwindow__window_size / 2;
	git_off_t len;
	git_mwindow *w;

	w = git__malloc(sizeof(*w));

	if (w == NULL)
		return NULL;

	memset(w, 0x0, sizeof(*w));
	w->offset = (offset / walign) * walign;

	len = size - w->offset;
	if (len > (git_off_t)git_mwindow__window_size)
		len = (git_off_t)git_mwindow__window_size;

	ctl->mapped += (size_t)len;

	while (git_mwindow__mapped_limit < ctl->mapped &&
			git_mwindow_close_lru(mwf) == 0) /* nop */;

	/*
	 * We treat `mapped_limit` as a soft limit. If we can't find a
	 * window to close and are above the limit, we still mmap the new
	 * window.
	 */

	if (git_futils_mmap_ro(&w->window_map, fd, w->offset, (size_t)len) < 0) {
		/*
		 * The first error might be down to memory fragmentation even if
		 * we're below our soft limits, so free up what we can and try again.
		 */

		while (git_mwindow_close_lru(mwf) == 0)
			/* nop */;

		if (git_futils_mmap_ro(&w->window_map, fd, w->offset, (size_t)len) < 0) {
			git__free(w);
			return NULL;
		}
	}

	ctl->mmap_calls++;
	ctl->open_windows++;

	if (ctl->mapped > ctl->peak_mapped)
		ctl->peak_mapped = ctl->mapped;

	if (ctl->open_windows > ctl->peak_open_windows)
		ctl->peak_open_windows = ctl->open_windows;

	return w;
}
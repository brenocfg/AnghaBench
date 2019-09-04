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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  _SC_PAGE_SIZE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

int git__page_size(size_t *page_size)
{
	long sc_page_size = sysconf(_SC_PAGE_SIZE);
	if (sc_page_size < 0) {
		git_error_set(GIT_ERROR_OS, "can't determine system page size");
		return -1;
	}
	*page_size = (size_t) sc_page_size;
	return 0;
}
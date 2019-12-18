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
 int /*<<< orphan*/  abort () ; 
 int creat (char const*,int) ; 
 int /*<<< orphan*/  malloc_printf (char*,char const*) ; 
 scalar_t__ opt_abort ; 

__attribute__((used)) static int
prof_dump_open_impl(bool propagate_err, const char *filename) {
	int fd;

	fd = creat(filename, 0644);
	if (fd == -1 && !propagate_err) {
		malloc_printf("<jemalloc>: creat(\"%s\"), 0644) failed\n",
		    filename);
		if (opt_abort) {
			abort();
		}
	}

	return fd;
}
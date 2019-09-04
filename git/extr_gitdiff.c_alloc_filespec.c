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
struct diff_filespec {int count; int is_binary; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEXPTR_ALLOC_STR (struct diff_filespec*,char const*,char const*) ; 

struct diff_filespec *alloc_filespec(const char *path)
{
	struct diff_filespec *spec;

	FLEXPTR_ALLOC_STR(spec, path, path);
	spec->count = 1;
	spec->is_binary = -1;
	return spec;
}
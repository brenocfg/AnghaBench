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
typedef  struct dirent dirent ;

/* Variables and functions */

__attribute__((used)) static int
alphasort_thunk(void *thunk, const void *p1, const void *p2)
{
	int (*dc)(const struct dirent **, const struct dirent **);

	dc = *(int (**)(const struct dirent **, const struct dirent **))thunk;
	return (dc((const struct dirent **)p1, (const struct dirent **)p2));
}
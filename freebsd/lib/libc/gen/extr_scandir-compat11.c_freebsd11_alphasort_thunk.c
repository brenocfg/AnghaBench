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
typedef  struct freebsd11_dirent freebsd11_dirent ;

/* Variables and functions */

__attribute__((used)) static int
freebsd11_alphasort_thunk(void *thunk, const void *p1, const void *p2)
{
	int (*dc)(const struct freebsd11_dirent **, const struct
	    freebsd11_dirent **);

	dc = *(int (**)(const struct freebsd11_dirent **,
	    const struct freebsd11_dirent **))thunk;
	return (dc((const struct freebsd11_dirent **)p1,
	    (const struct freebsd11_dirent **)p2));
}
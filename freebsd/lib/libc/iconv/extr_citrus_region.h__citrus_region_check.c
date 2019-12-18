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
struct _citrus_region {size_t r_size; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
_citrus_region_check(const struct _citrus_region *r, size_t ofs, size_t sz)
{

	return (r->r_size >= ofs + sz ? 0 : -1);
}
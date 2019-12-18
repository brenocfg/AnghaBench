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
typedef  int /*<<< orphan*/  uint8_t ;
struct _citrus_region {scalar_t__ r_head; } ;

/* Variables and functions */

__attribute__((used)) static __inline void *
_citrus_region_offset(const struct _citrus_region *r, size_t pos)
{

	return ((void *)((uint8_t *)r->r_head + pos));
}
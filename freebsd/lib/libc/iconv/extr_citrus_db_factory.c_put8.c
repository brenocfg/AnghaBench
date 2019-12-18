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
struct _region {int dummy; } ;

/* Variables and functions */
 scalar_t__ _region_offset (struct _region*,size_t) ; 

__attribute__((used)) static __inline void
put8(struct _region *r, size_t *rofs, uint8_t val)
{

	*(uint8_t *)_region_offset(r, *rofs) = val;
	*rofs += 1;
}
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
struct _citrus_region {int dummy; } ;

/* Variables and functions */
 scalar_t__ _citrus_region_offset (struct _citrus_region const*,size_t) ; 

__attribute__((used)) static __inline uint8_t
_citrus_region_peek8(const struct _citrus_region *r, size_t pos)
{

	return (*(uint8_t *)_citrus_region_offset(r, pos));
}
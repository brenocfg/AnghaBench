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
typedef  int /*<<< orphan*/  uint32_t ;
struct _citrus_region {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _citrus_region_offset (struct _citrus_region const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static __inline uint32_t
_citrus_region_peek32(const struct _citrus_region *r, size_t pos)
{
	uint32_t val;

	memcpy(&val, _citrus_region_offset(r, pos), (size_t)4);
	return (val);
}
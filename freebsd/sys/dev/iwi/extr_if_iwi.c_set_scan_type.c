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
typedef  int uint8_t ;
struct iwi_scan_ext {int* scan_type; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
set_scan_type(struct iwi_scan_ext *scan, int ix, int scan_type)
{
	uint8_t *st = &scan->scan_type[ix / 2];
	if (ix % 2)
		*st = (*st & 0xf0) | ((scan_type & 0xf) << 0);
	else
		*st = (*st & 0x0f) | ((scan_type & 0xf) << 4);
}
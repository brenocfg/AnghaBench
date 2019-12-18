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

__attribute__((used)) static inline bool intersects(unsigned long addr0, unsigned long size0,
			      unsigned long addr1, unsigned long size1)
{
	return addr0 + size0 > addr1 && addr1 + size1 > addr0;
}
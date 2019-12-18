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
typedef  size_t u32 ;
struct ecx_plat_data {int* port_to_sgpio; } ;

/* Variables and functions */

__attribute__((used)) static inline int sgpio_bit_shift(struct ecx_plat_data *pdata, u32 port,
				u32 shift)
{
	return 1 << (3 * pdata->port_to_sgpio[port] + shift);
}
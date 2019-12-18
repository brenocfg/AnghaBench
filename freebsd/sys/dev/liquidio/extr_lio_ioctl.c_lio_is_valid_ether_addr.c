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

/* Variables and functions */

__attribute__((used)) static inline bool
lio_is_valid_ether_addr(const uint8_t *addr)
{

	return (!(0x01 & addr[0]) && !((addr[0] + addr[1] + addr[2] + addr[3] +
					addr[4] + addr[5]) == 0x00));
}
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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ F_TLV_PDAT ; 
 scalar_t__ F_TLV_REST ; 

__attribute__((used)) static inline int pd_valid(uint16_t pd)
{
	if (pd >= F_TLV_PDAT && pd <= F_TLV_REST)
		return 1;
	return 0;
}
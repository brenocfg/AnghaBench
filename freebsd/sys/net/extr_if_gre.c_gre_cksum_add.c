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

__attribute__((used)) static __inline uint16_t
gre_cksum_add(uint16_t sum, uint16_t a)
{
	uint16_t res;

	res = sum + a;
	return (res + (res < a));
}
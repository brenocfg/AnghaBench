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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */

uint64_t
nae_tx_desc(u_int type, u_int rdex, u_int fbid, u_int len, uint64_t addr)
{
	return ((uint64_t)type  << 62) |
		((uint64_t)rdex << 61) |
		((uint64_t)fbid << 54) |
		((uint64_t)len  << 40) | addr;
}
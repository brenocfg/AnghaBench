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

/* Variables and functions */

int ibnd_is_xsigo_hca(uint64_t guid)
{
	/* NodeType 2 is HCA */
	if ((guid & 0xffffffff00000000ULL) == 0x0013970200000000ULL)
		return 1;
	else
		return 0;
}
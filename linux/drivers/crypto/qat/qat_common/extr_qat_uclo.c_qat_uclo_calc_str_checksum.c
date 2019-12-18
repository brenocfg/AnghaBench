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
 unsigned int qat_uclo_calc_checksum (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int qat_uclo_calc_str_checksum(char *ptr, int num)
{
	unsigned int chksum = 0;

	if (ptr)
		while (num--)
			chksum = qat_uclo_calc_checksum(chksum, *ptr++);
	return chksum;
}
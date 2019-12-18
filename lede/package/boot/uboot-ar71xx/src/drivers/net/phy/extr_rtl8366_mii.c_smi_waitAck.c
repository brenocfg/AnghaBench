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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ smi_readBits (int) ; 

__attribute__((used)) static int smi_waitAck(void)
{
    uint32_t retry = 0;

	while (smi_readBits(1)) {
		if (retry++ == 5)
			return -1;
	}

	return 0;

}
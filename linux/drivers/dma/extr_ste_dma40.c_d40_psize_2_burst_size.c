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
 int STEDMA40_PSIZE_LOG_1 ; 
 int STEDMA40_PSIZE_PHY_1 ; 

__attribute__((used)) static int d40_psize_2_burst_size(bool is_log, int psize)
{
	if (is_log) {
		if (psize == STEDMA40_PSIZE_LOG_1)
			return 1;
	} else {
		if (psize == STEDMA40_PSIZE_PHY_1)
			return 1;
	}

	return 2 << psize;
}
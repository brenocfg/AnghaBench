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
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int AR512_NF_CAL_HIST_MAX ; 
 int /*<<< orphan*/  OS_MEMCPY (scalar_t__*,scalar_t__ const*,int) ; 

int16_t 
ar5212GetNfHistMid(const int16_t calData[AR512_NF_CAL_HIST_MAX])
{
	int16_t sort[AR512_NF_CAL_HIST_MAX];
	int i, j;

	OS_MEMCPY(sort, calData, AR512_NF_CAL_HIST_MAX*sizeof(int16_t));
	for (i = 0; i < AR512_NF_CAL_HIST_MAX-1; i ++) {
		for (j = 1; j < AR512_NF_CAL_HIST_MAX-i; j ++) {
			if (sort[j] > sort[j-1]) {
				int16_t nf = sort[j];
				sort[j] = sort[j-1];
				sort[j-1] = nf;
			}
		}
	}
	return sort[(AR512_NF_CAL_HIST_MAX-1)>>1];
}
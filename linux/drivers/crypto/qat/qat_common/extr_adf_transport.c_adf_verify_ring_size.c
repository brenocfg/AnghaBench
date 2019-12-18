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
typedef  int uint32_t ;

/* Variables and functions */
 int ADF_DEFAULT_RING_SIZE ; 
 int ADF_MAX_RING_SIZE ; 
 int ADF_MIN_RING_SIZE ; 
 int ADF_SIZE_TO_RING_SIZE_IN_BYTES (int) ; 

__attribute__((used)) static int adf_verify_ring_size(uint32_t msg_size, uint32_t msg_num)
{
	int i = ADF_MIN_RING_SIZE;

	for (; i <= ADF_MAX_RING_SIZE; i++)
		if ((msg_size * msg_num) == ADF_SIZE_TO_RING_SIZE_IN_BYTES(i))
			return i;

	return ADF_DEFAULT_RING_SIZE;
}
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
 int NUM_PACKET_SIZE_BINS ; 
 int* packet_size_bins ; 

__attribute__((used)) static __inline int
size_to_bin(int size) 
{
#if NUM_PACKET_SIZE_BINS > 1
	if (size <= packet_size_bins[0])
		return 0;
#endif
#if NUM_PACKET_SIZE_BINS > 2
	if (size <= packet_size_bins[1])
		return 1;
#endif
#if NUM_PACKET_SIZE_BINS > 3
	if (size <= packet_size_bins[2])
		return 2;
#endif
#if NUM_PACKET_SIZE_BINS > 4
#error "add support for more packet sizes"
#endif
	return NUM_PACKET_SIZE_BINS-1;
}
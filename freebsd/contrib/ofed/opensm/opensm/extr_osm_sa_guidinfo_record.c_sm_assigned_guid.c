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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;

/* Variables and functions */
 scalar_t__ OSM_VENDOR_ID_OPENIB ; 
 int /*<<< orphan*/  cl_hton64 (int) ; 

__attribute__((used)) static ib_net64_t sm_assigned_guid(uint8_t assigned_byte)
{
	static uint32_t uniq_count;

	if (++uniq_count == 0) {
		uniq_count--;
		return 0;
	}
	return cl_hton64(((uint64_t) uniq_count) |
			 (((uint64_t) assigned_byte) << 32) |
			 (((uint64_t) OSM_VENDOR_ID_OPENIB) << 40));
}
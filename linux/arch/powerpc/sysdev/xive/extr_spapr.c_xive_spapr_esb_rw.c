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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  XIVE_ESB_FLAG_STORE ; 
 long plpar_int_esb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long*) ; 

__attribute__((used)) static u64 xive_spapr_esb_rw(u32 lisn, u32 offset, u64 data, bool write)
{
	unsigned long read_data;
	long rc;

	rc = plpar_int_esb(write ? XIVE_ESB_FLAG_STORE : 0,
			   lisn, offset, data, &read_data);
	if (rc)
		return -1;

	return write ? 0 : read_data;
}
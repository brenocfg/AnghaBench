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
struct ib_class_port_info {int /*<<< orphan*/  capability_mask; } ;
typedef  int /*<<< orphan*/  cpi ;

/* Variables and functions */
 int IB_MAD_RESULT_REPLY ; 
 int IB_MAD_RESULT_SUCCESS ; 
 int /*<<< orphan*/  IB_PMA_CLASS_CAP_EXT_WIDTH ; 
 int /*<<< orphan*/  memcpy (void*,struct ib_class_port_info*,int) ; 

__attribute__((used)) static int iboe_process_mad_port_info(void *out_mad)
{
	struct ib_class_port_info cpi = {};

	cpi.capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;
	memcpy(out_mad, &cpi, sizeof(cpi));
	return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
}
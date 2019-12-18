#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uvcb ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int len; int /*<<< orphan*/  cmd; } ;
struct uv_cb_qui {scalar_t__ inst_calls_list; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_UVC_CMD_REMOVE_SHARED_ACCESS ; 
 int /*<<< orphan*/  BIT_UVC_CMD_SET_SHARED_ACCESS ; 
 int /*<<< orphan*/  UVC_CMD_QUI ; 
 int prot_virt_guest ; 
 scalar_t__ test_bit_inv (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  test_facility (int) ; 
 scalar_t__ uv_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uv_query_info(void)
{
	struct uv_cb_qui uvcb = {
		.header.cmd = UVC_CMD_QUI,
		.header.len = sizeof(uvcb)
	};

	if (!test_facility(158))
		return;

	if (uv_call(0, (uint64_t)&uvcb))
		return;

	if (test_bit_inv(BIT_UVC_CMD_SET_SHARED_ACCESS, (unsigned long *)uvcb.inst_calls_list) &&
	    test_bit_inv(BIT_UVC_CMD_REMOVE_SHARED_ACCESS, (unsigned long *)uvcb.inst_calls_list))
		prot_virt_guest = 1;
}
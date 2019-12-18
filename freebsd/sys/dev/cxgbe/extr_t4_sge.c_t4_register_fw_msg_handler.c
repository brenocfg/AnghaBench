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
typedef  int /*<<< orphan*/ * fw_msg_handler_t ;

/* Variables and functions */
 int FW6_TYPE_RSSCPL ; 
 int FW_TYPE_RSSCPL ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t*,uintptr_t) ; 
 int nitems (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** t4_fw_msg_handler ; 

void
t4_register_fw_msg_handler(int type, fw_msg_handler_t h)
{
	uintptr_t *loc;

	MPASS(type < nitems(t4_fw_msg_handler));
	MPASS(h == NULL || t4_fw_msg_handler[type] == NULL);
	/*
	 * These are dispatched by the handler for FW{4|6}_CPL_MSG using the CPL
	 * handler dispatch table.  Reject any attempt to install a handler for
	 * this subtype.
	 */
	MPASS(type != FW_TYPE_RSSCPL);
	MPASS(type != FW6_TYPE_RSSCPL);

	loc = (uintptr_t *)&t4_fw_msg_handler[type];
	atomic_store_rel_ptr(loc, (uintptr_t)h);
}
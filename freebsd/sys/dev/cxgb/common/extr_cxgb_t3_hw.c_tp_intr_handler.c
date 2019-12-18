#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct TYPE_6__ {scalar_t__ rev; } ;
struct TYPE_7__ {TYPE_1__ params; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_INT_CAUSE ; 
#define  F_FLMRXFLSTEMPTY 129 
#define  F_FLMTXFLSTEMPTY 128 
 scalar_t__ T3_REV_C ; 
 int /*<<< orphan*/  t3_fatal_err (TYPE_2__*) ; 
 scalar_t__ t3_handle_intr_status (TYPE_2__*,int /*<<< orphan*/ ,int,struct intr_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tp_intr_handler(adapter_t *adapter)
{
	static struct intr_info tp_intr_info[] = {
		{ 0xffffff,  "TP parity error", -1, 1 },
		{ 0x1000000, "TP out of Rx pages", -1, 1 },
		{ 0x2000000, "TP out of Tx pages", -1, 1 },
		{ 0 }
	};
	static struct intr_info tp_intr_info_t3c[] = {
		{ 0x1fffffff,  "TP parity error", -1, 1 },
		{ F_FLMRXFLSTEMPTY, "TP out of Rx pages", -1, 1 },
		{ F_FLMTXFLSTEMPTY, "TP out of Tx pages", -1, 1 },
		{ 0 }
	};

	if (t3_handle_intr_status(adapter, A_TP_INT_CAUSE, 0xffffffff,
				  adapter->params.rev < T3_REV_C ?
					tp_intr_info : tp_intr_info_t3c, NULL))
		t3_fatal_err(adapter);
}
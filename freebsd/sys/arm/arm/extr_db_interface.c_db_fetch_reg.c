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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  tf_pc; int /*<<< orphan*/  tf_svc_lr; int /*<<< orphan*/  tf_svc_sp; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_r7; int /*<<< orphan*/  tf_r6; int /*<<< orphan*/  tf_r5; int /*<<< orphan*/  tf_r4; int /*<<< orphan*/  tf_r3; int /*<<< orphan*/  tf_r2; int /*<<< orphan*/  tf_r1; int /*<<< orphan*/  tf_r0; } ;

/* Variables and functions */
 TYPE_1__* kdb_frame ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static u_int
db_fetch_reg(int reg)
{

	switch (reg) {
	case 0:
		return (kdb_frame->tf_r0);
	case 1:
		return (kdb_frame->tf_r1);
	case 2:
		return (kdb_frame->tf_r2);
	case 3:
		return (kdb_frame->tf_r3);
	case 4:
		return (kdb_frame->tf_r4);
	case 5:
		return (kdb_frame->tf_r5);
	case 6:
		return (kdb_frame->tf_r6);
	case 7:
		return (kdb_frame->tf_r7);
	case 8:
		return (kdb_frame->tf_r8);
	case 9:
		return (kdb_frame->tf_r9);
	case 10:
		return (kdb_frame->tf_r10);
	case 11:
		return (kdb_frame->tf_r11);
	case 12:
		return (kdb_frame->tf_r12);
	case 13:
		return (kdb_frame->tf_svc_sp);
	case 14:
		return (kdb_frame->tf_svc_lr);
	case 15:
		return (kdb_frame->tf_pc);
	default:
		panic("db_fetch_reg: botch");
	}
}
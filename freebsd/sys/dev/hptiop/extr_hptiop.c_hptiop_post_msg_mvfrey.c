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
typedef  int /*<<< orphan*/  u_int32_t ;
struct hpt_iop_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_RD4_MVFREY2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_MVFREY2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f0_to_cpu_msg_a ; 

__attribute__((used)) static void hptiop_post_msg_mvfrey(struct hpt_iop_hba *hba, u_int32_t msg)
{
	BUS_SPACE_WRT4_MVFREY2(f0_to_cpu_msg_a, msg);
	BUS_SPACE_RD4_MVFREY2(f0_to_cpu_msg_a);
}
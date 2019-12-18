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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_kg_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  build_ar_bind_cls_plan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_kg_write_ar_wait (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_kg_write_cpp (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_pe_all_cls_plan(struct fman_kg_regs *regs, uint8_t hwport_id)
{
	uint32_t ar;

	fman_kg_write_cpp(regs, 0);

	ar = build_ar_bind_cls_plan(hwport_id, TRUE);
	fman_kg_write_ar_wait(regs, ar);
}
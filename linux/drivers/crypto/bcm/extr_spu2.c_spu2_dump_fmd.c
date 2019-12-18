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
struct SPU2_FMD {int /*<<< orphan*/  ctrl3; int /*<<< orphan*/  ctrl2; int /*<<< orphan*/  ctrl1; int /*<<< orphan*/  ctrl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu2_dump_fmd_ctrl0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu2_dump_fmd_ctrl1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu2_dump_fmd_ctrl2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu2_dump_fmd_ctrl3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spu2_dump_fmd(struct SPU2_FMD *fmd)
{
	spu2_dump_fmd_ctrl0(le64_to_cpu(fmd->ctrl0));
	spu2_dump_fmd_ctrl1(le64_to_cpu(fmd->ctrl1));
	spu2_dump_fmd_ctrl2(le64_to_cpu(fmd->ctrl2));
	spu2_dump_fmd_ctrl3(le64_to_cpu(fmd->ctrl3));
}
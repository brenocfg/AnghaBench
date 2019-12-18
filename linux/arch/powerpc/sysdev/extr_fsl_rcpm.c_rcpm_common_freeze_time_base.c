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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcpm_common_freeze_time_base(u32 *tben_reg, int freeze)
{
	static u32 mask;

	if (freeze) {
		mask = in_be32(tben_reg);
		clrbits32(tben_reg, mask);
	} else {
		setbits32(tben_reg, mask);
	}

	/* read back to push the previous write */
	in_be32(tben_reg);
}
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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ti_scm_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_scm_sc ; 

int
ti_scm_reg_read_4(uint32_t reg, uint32_t *val)
{
	if (!ti_scm_sc)
		return (ENXIO);

	*val = ti_scm_read_4(ti_scm_sc, reg);
	return (0);
}
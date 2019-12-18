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
typedef  int uint8_t ;
struct as3722_reg_sc {TYPE_1__* def; int /*<<< orphan*/  base_sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_enable_mask; int /*<<< orphan*/  ext_enable_reg; } ;

/* Variables and functions */
 int RM1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
as3722_reg_extreg_setup(struct as3722_reg_sc *sc, int ext_pwr_ctrl)
{
	uint8_t val;
	int rv;

	val =  ext_pwr_ctrl << (ffs(sc->def->ext_enable_mask) - 1);
	rv = RM1(sc->base_sc, sc->def->ext_enable_reg,
	    sc->def->ext_enable_mask, val);
	return (rv);
}
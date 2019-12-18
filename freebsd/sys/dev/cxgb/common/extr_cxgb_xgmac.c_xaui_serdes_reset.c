#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct cmac {scalar_t__ offset; TYPE_3__* adapter; } ;
struct TYPE_7__ {unsigned int const* xauicfg; } ;
struct TYPE_8__ {TYPE_1__ vpd; } ;
struct TYPE_9__ {TYPE_2__ params; } ;
typedef  TYPE_3__ adapter_t ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int const*) ; 
 scalar_t__ A_XGM_SERDES_CTRL0 ; 
#define  F_PWRDN0 137 
#define  F_PWRDN1 136 
#define  F_PWRDN2 135 
#define  F_PWRDN3 134 
#define  F_RESET0 133 
#define  F_RESET1 132 
#define  F_RESET2 131 
#define  F_RESET3 130 
#define  F_RESETPLL01 129 
#define  F_RESETPLL23 128 
 size_t macidx (struct cmac*) ; 
 int /*<<< orphan*/  t3_read_reg (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  t3_set_reg_field (TYPE_3__*,scalar_t__,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_3__*,scalar_t__,unsigned int const) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void xaui_serdes_reset(struct cmac *mac)
{
	static const unsigned int clear[] = {
		F_PWRDN0 | F_PWRDN1,    F_RESETPLL01,    F_RESET0 | F_RESET1,
	     	F_PWRDN2 | F_PWRDN3,    F_RESETPLL23,    F_RESET2 | F_RESET3
	};

	int i;
	adapter_t *adap = mac->adapter;
	u32 ctrl = A_XGM_SERDES_CTRL0 + mac->offset;

	t3_write_reg(adap, ctrl, adap->params.vpd.xauicfg[macidx(mac)] |
		     F_RESET3 | F_RESET2 | F_RESET1 | F_RESET0 |
		     F_PWRDN3 | F_PWRDN2 | F_PWRDN1 | F_PWRDN0 |
		     F_RESETPLL23 | F_RESETPLL01);
	(void)t3_read_reg(adap, ctrl);
	udelay(15);

	for (i = 0; i < ARRAY_SIZE(clear); i++) {
		t3_set_reg_field(adap, ctrl, clear[i], 0);
		udelay(15);
	}
}
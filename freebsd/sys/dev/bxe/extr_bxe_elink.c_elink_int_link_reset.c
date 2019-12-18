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
struct elink_phy {int dummy; } ;
struct elink_params {int port; int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_3_CLEAR ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void elink_int_link_reset(struct elink_phy *phy,
				 struct elink_params *params)
{
	/* Reset the SerDes/XGXS */
	REG_WR(params->sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_3_CLEAR,
	       (0x1ff << (params->port*16)));
}
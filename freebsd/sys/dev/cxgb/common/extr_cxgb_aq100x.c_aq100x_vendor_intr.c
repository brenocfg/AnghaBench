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
struct cphy {scalar_t__ addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 unsigned int AQBIT (int) ; 
 int /*<<< orphan*/  A_T3DBG_GPIO_EN ; 
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  F_GPIO10_OUT_VAL ; 
 int /*<<< orphan*/  F_GPIO6_OUT_VAL ; 
 int /*<<< orphan*/  MDIO_DEV_VEND1 ; 
 unsigned int aq100x_temperature (struct cphy*) ; 
 int cphy_cause_alarm ; 
 int e ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aq100x_vendor_intr(struct cphy *phy, int *rc)
{
	int err;
	unsigned int cause, v;

	err = mdio_read(phy, MDIO_DEV_VEND1, 0xfc01, &cause);
	if (err)
		return (err);

	if (cause & AQBIT(2)) {
		err = mdio_read(phy, MDIO_DEV_VEND1, 0xcc00, &v);
		if (err)
			return (err);

		if (v & AQBIT(e)) {
			CH_WARN(phy->adapter, "PHY%d: temperature is now %dC\n",
			    phy->addr, aq100x_temperature(phy));

			t3_set_reg_field(phy->adapter, A_T3DBG_GPIO_EN,
			    phy->addr ? F_GPIO10_OUT_VAL : F_GPIO6_OUT_VAL, 0);

			*rc |= cphy_cause_alarm;
		}

		cause &= ~4;
	}

	if (cause)
		CH_WARN(phy->adapter, "PHY%d: unhandled vendor interrupt"
		    " (0x%x)\n", phy->addr, cause);

	return (0);

}
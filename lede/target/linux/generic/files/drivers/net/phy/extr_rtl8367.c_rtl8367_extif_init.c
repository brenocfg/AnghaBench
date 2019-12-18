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
struct rtl8367_extif_config {int mode; int /*<<< orphan*/  rxdelay; int /*<<< orphan*/  txdelay; int /*<<< orphan*/  ability; } ;
struct rtl8366_smi {int dummy; } ;
typedef  enum rtl8367_extif_mode { ____Placeholder_rtl8367_extif_mode } rtl8367_extif_mode ;

/* Variables and functions */
 int RTL8367_EXTIF_MODE_DISABLED ; 
 int rtl8367_extif_set_force (struct rtl8366_smi*,int,int /*<<< orphan*/ *) ; 
 int rtl8367_extif_set_mode (struct rtl8366_smi*,int,int) ; 
 int rtl8367_extif_set_rgmii_delay (struct rtl8366_smi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8367_extif_init(struct rtl8366_smi *smi, int id,
			      struct rtl8367_extif_config *cfg)
{
	enum rtl8367_extif_mode mode;
	int err;

	mode = (cfg) ? cfg->mode : RTL8367_EXTIF_MODE_DISABLED;

	err = rtl8367_extif_set_mode(smi, id, mode);
	if (err)
		return err;

	if (mode != RTL8367_EXTIF_MODE_DISABLED) {
		err = rtl8367_extif_set_force(smi, id, &cfg->ability);
		if (err)
			return err;

		err = rtl8367_extif_set_rgmii_delay(smi, id, cfg->txdelay,
						     cfg->rxdelay);
		if (err)
			return err;
	}

	return 0;
}
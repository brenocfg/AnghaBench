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
typedef  int u_int8_t ;
struct agg_info {int curpwr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_REG_POWER ; 
 int AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
#define  PCI_POWERSTATE_D0 131 
#define  PCI_POWERSTATE_D1 130 
#define  PCI_POWERSTATE_D2 129 
#define  PCI_POWERSTATE_D3 128 
 int /*<<< orphan*/  PORT_HOSTINT_CTRL ; 
 int /*<<< orphan*/  PORT_HOSTINT_STAT ; 
 int /*<<< orphan*/  PORT_RINGBUS_CTRL ; 
 int RINGBUS_CTRL_ACLINK_ENABLED ; 
 int RINGBUS_CTRL_RINGBUS_ENABLED ; 
 int /*<<< orphan*/  agg_init (struct agg_info*) ; 
 int agg_rdcodec (struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_wrcodec (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  wp_stoptimer (struct agg_info*) ; 

__attribute__((used)) static void
agg_power(struct agg_info *ess, int status)
{
	u_int8_t lastpwr;

	lastpwr = ess->curpwr;
	if (lastpwr == status)
		return;

	switch (status) {
	case PCI_POWERSTATE_D0:
	case PCI_POWERSTATE_D1:
		switch (lastpwr) {
		case PCI_POWERSTATE_D2:
			pci_set_powerstate(ess->dev, status);
			/* Turn on PCM-related parts. */
			agg_wrcodec(ess, AC97_REG_POWER, 0);
			DELAY(100);
#if 0
			if ((agg_rdcodec(ess, AC97_REG_POWER) & 3) != 3)
				device_printf(ess->dev,
				    "warning: codec not ready.\n");
#endif
			AGG_WR(ess, PORT_RINGBUS_CTRL,
			       (AGG_RD(ess, PORT_RINGBUS_CTRL, 4)
				& ~RINGBUS_CTRL_ACLINK_ENABLED)
			       | RINGBUS_CTRL_RINGBUS_ENABLED, 4);
			DELAY(50);
			AGG_WR(ess, PORT_RINGBUS_CTRL,
			       AGG_RD(ess, PORT_RINGBUS_CTRL, 4)
			       | RINGBUS_CTRL_ACLINK_ENABLED, 4);
			break;
		case PCI_POWERSTATE_D3:
			/* Initialize. */
			pci_set_powerstate(ess->dev, PCI_POWERSTATE_D0);
			DELAY(100);
			agg_init(ess);
			/* FALLTHROUGH */
		case PCI_POWERSTATE_D0:
		case PCI_POWERSTATE_D1:
			pci_set_powerstate(ess->dev, status);
			break;
		}
		break;
	case PCI_POWERSTATE_D2:
		switch (lastpwr) {
		case PCI_POWERSTATE_D3:
			/* Initialize. */
			pci_set_powerstate(ess->dev, PCI_POWERSTATE_D0);
			DELAY(100);
			agg_init(ess);
			/* FALLTHROUGH */
		case PCI_POWERSTATE_D0:
		case PCI_POWERSTATE_D1:
			/* Turn off PCM-related parts. */
			AGG_WR(ess, PORT_RINGBUS_CTRL,
			       AGG_RD(ess, PORT_RINGBUS_CTRL, 4)
			       & ~RINGBUS_CTRL_RINGBUS_ENABLED, 4);
			DELAY(100);
			agg_wrcodec(ess, AC97_REG_POWER, 0x300);
			DELAY(100);
			break;
		}
		pci_set_powerstate(ess->dev, status);
		break;
	case PCI_POWERSTATE_D3:
		/* Entirely power down. */
		agg_wrcodec(ess, AC97_REG_POWER, 0xdf00);
		DELAY(100);
		AGG_WR(ess, PORT_RINGBUS_CTRL, 0, 4);
		/*DELAY(1);*/
		if (lastpwr != PCI_POWERSTATE_D2)
			wp_stoptimer(ess);
		AGG_WR(ess, PORT_HOSTINT_CTRL, 0, 2);
		AGG_WR(ess, PORT_HOSTINT_STAT, 0xff, 1);
		pci_set_powerstate(ess->dev, status);
		break;
	default:
		/* Invalid power state; let it ignored. */
		status = lastpwr;
		break;
	}

	ess->curpwr = status;
}
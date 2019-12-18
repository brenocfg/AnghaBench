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
struct sc_info {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_ACCAD ; 
 int /*<<< orphan*/  CS4281PCI_ACCDA ; 
 int /*<<< orphan*/  CS4281PCI_ACCTL ; 
 int CS4281PCI_ACCTL_CRW ; 
 int CS4281PCI_ACCTL_DCV ; 
 int CS4281PCI_ACCTL_ESYN ; 
 int CS4281PCI_ACCTL_VFRM ; 
 int /*<<< orphan*/  CS4281PCI_ACSDA ; 
 int /*<<< orphan*/  CS4281PCI_ACSTS ; 
 int /*<<< orphan*/  CS4281PCI_ACSTS_VSTS ; 
 int cs4281_rd (struct sc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ cs4281_waitclr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ cs4281_waitset (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cs4281_rdcd(kobj_t obj, void *devinfo, int regno)
{
    struct sc_info *sc = (struct sc_info *)devinfo;
    int codecno;

    codecno = regno >> 8;
    regno &= 0xff;

    /* Remove old state */
    cs4281_rd(sc, CS4281PCI_ACSDA);

    /* Fill in AC97 register value request form */
    cs4281_wr(sc, CS4281PCI_ACCAD, regno);
    cs4281_wr(sc, CS4281PCI_ACCDA, 0);
    cs4281_wr(sc, CS4281PCI_ACCTL, CS4281PCI_ACCTL_ESYN |
	      CS4281PCI_ACCTL_VFRM | CS4281PCI_ACCTL_DCV |
	      CS4281PCI_ACCTL_CRW);

    /* Wait for read to complete */
    if (cs4281_waitclr(sc, CS4281PCI_ACCTL, CS4281PCI_ACCTL_DCV, 250) == 0) {
	device_printf(sc->dev, "cs4281_rdcd: DCV did not go\n");
	return -1;
    }

    /* Wait for valid status */
    if (cs4281_waitset(sc, CS4281PCI_ACSTS, CS4281PCI_ACSTS_VSTS, 250) == 0) {
	device_printf(sc->dev,"cs4281_rdcd: VSTS did not come\n");
	return -1;
    }

    return cs4281_rd(sc, CS4281PCI_ACSDA);
}
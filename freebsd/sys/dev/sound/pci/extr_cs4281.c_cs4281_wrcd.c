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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_ACCAD ; 
 int /*<<< orphan*/  CS4281PCI_ACCDA ; 
 int /*<<< orphan*/  CS4281PCI_ACCTL ; 
 int CS4281PCI_ACCTL_DCV ; 
 int CS4281PCI_ACCTL_ESYN ; 
 int CS4281PCI_ACCTL_VFRM ; 
 scalar_t__ cs4281_waitclr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cs4281_wrcd(kobj_t obj, void *devinfo, int regno, u_int32_t data)
{
    struct sc_info *sc = (struct sc_info *)devinfo;
    int codecno;

    codecno = regno >> 8;
    regno &= 0xff;

    cs4281_wr(sc, CS4281PCI_ACCAD, regno);
    cs4281_wr(sc, CS4281PCI_ACCDA, data);
    cs4281_wr(sc, CS4281PCI_ACCTL, CS4281PCI_ACCTL_ESYN |
	      CS4281PCI_ACCTL_VFRM | CS4281PCI_ACCTL_DCV);

    if (cs4281_waitclr(sc, CS4281PCI_ACCTL, CS4281PCI_ACCTL_DCV, 250) == 0) {
	device_printf(sc->dev,"cs4281_wrcd: DCV did not go\n");
    }

    return 0;
}
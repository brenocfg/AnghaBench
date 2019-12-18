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
struct snps_dwc3_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GCTL ; 
 int /*<<< orphan*/  DWC3_GCTL_PRTCAPDIR_HOST ; 
 int /*<<< orphan*/  DWC3_GCTL_PRTCAPDIR_MASK ; 
 int /*<<< orphan*/  DWC3_READ (struct snps_dwc3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_WRITE (struct snps_dwc3_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snps_dwc3_configure_host(struct snps_dwc3_softc *sc)
{
	uint32_t reg;

	reg = DWC3_READ(sc, DWC3_GCTL);
	reg &= ~DWC3_GCTL_PRTCAPDIR_MASK;
	reg |= DWC3_GCTL_PRTCAPDIR_HOST;
	DWC3_WRITE(sc, DWC3_GCTL, reg);
}
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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct intr_irqsrc {int dummy; } ;
struct al_msix_softc {int irq_min; scalar_t__ base_addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERR_NOT_IN_MAP ; 
 int al_find_intr_pos_in_map (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 scalar_t__ bootverbose ; 
 struct al_msix_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_msix_map_msi(device_t dev, device_t child, struct intr_irqsrc *isrc,
    uint64_t *addr, uint32_t *data)
{
	struct al_msix_softc *sc;
	int i, spi;

	sc = device_get_softc(dev);

	i = al_find_intr_pos_in_map(dev, isrc);
	if (i == ERR_NOT_IN_MAP)
		return (EINVAL);

	spi = sc->irq_min + i;

	/*
	 * MSIX message address format:
	 * [63:20] - MSIx TBAR
	 *           Same value as the MSIx Translation Base  Address Register
	 * [19]    - WFE_EXIT
	 *           Once set by MSIx message, an EVENTI is signal to the CPUs
	 *           cluster specified by ‘Local GIC Target List’
	 * [18:17] - Target GIC ID
	 *           Specifies which IO-GIC (external shared GIC) is targeted
	 *           0: Local GIC, as specified by the Local GIC Target List
	 *           1: IO-GIC 0
	 *           2: Reserved
	 *           3: Reserved
	 * [16:13] - Local GIC Target List
	 *           Specifies the Local GICs list targeted by this MSIx
	 *           message.
	 *           [16]  If set, SPIn is set in Cluster 0 local GIC
	 *           [15:13] Reserved
	 *           [15]  If set, SPIn is set in Cluster 1 local GIC
	 *           [14]  If set, SPIn is set in Cluster 2 local GIC
	 *           [13]  If set, SPIn is set in Cluster 3 local GIC
	 * [12:3]  - SPIn
	 *           Specifies the SPI (Shared Peripheral Interrupt) index to
	 *           be set in target GICs
	 *           Notes:
	 *           If targeting any local GIC than only SPI[249:0] are valid
	 * [2]     - Function vector
	 *           MSI Data vector extension hint
	 * [1:0]   - Reserved
	 *           Must be set to zero
	 */
	*addr = (uint64_t)sc->base_addr + (uint64_t)((1 << 16) + (spi << 3));
	*data = 0;

	if (bootverbose)
		device_printf(dev, "MSI mapping: SPI: %d addr: %jx data: %x\n",
		    spi, (uintmax_t)*addr, *data);
	return (0);
}
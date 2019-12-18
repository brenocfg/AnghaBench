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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; } ;
struct rue_softc {TYPE_1__ sc_ue; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  MII_ANAR 134 
#define  MII_ANER 133 
#define  MII_ANLPAR 132 
#define  MII_BMCR 131 
#define  MII_BMSR 130 
#define  MII_PHYIDR1 129 
#define  MII_PHYIDR2 128 
 int /*<<< orphan*/  RUE_AER ; 
 int /*<<< orphan*/  RUE_ANAR ; 
 int /*<<< orphan*/  RUE_ANLP ; 
 int /*<<< orphan*/  RUE_BMCR ; 
 int /*<<< orphan*/  RUE_BMSR ; 
 int /*<<< orphan*/  RUE_LOCK (struct rue_softc*) ; 
 int RUE_REG_MAX ; 
 int RUE_REG_MIN ; 
 int /*<<< orphan*/  RUE_UNLOCK (struct rue_softc*) ; 
 struct rue_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rue_csr_write_1 (struct rue_softc*,int,int) ; 
 int /*<<< orphan*/  rue_csr_write_2 (struct rue_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rue_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct rue_softc *sc = device_get_softc(dev);
	uint16_t ruereg;
	int locked;

	if (phy != 0)		/* RTL8150 supports PHY == 0, only */
		return (0);

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		RUE_LOCK(sc);

	switch (reg) {
	case MII_BMCR:
		ruereg = RUE_BMCR;
		break;
	case MII_BMSR:
		ruereg = RUE_BMSR;
		break;
	case MII_ANAR:
		ruereg = RUE_ANAR;
		break;
	case MII_ANER:
		ruereg = RUE_AER;
		break;
	case MII_ANLPAR:
		ruereg = RUE_ANLP;
		break;
	case MII_PHYIDR1:
	case MII_PHYIDR2:
		goto done;
	default:
		if (RUE_REG_MIN <= reg && reg <= RUE_REG_MAX) {
			rue_csr_write_1(sc, reg, data);
			goto done;
		}
		device_printf(sc->sc_ue.ue_dev, " bad phy register\n");
		goto done;
	}
	rue_csr_write_2(sc, ruereg, data);
done:
	if (!locked)
		RUE_UNLOCK(sc);
	return (0);
}
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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct arswitch_softc {int page; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MDIO_WRITEREG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
arswitch_split_setpage(device_t dev, uint32_t addr, uint16_t *phy,
    uint16_t *reg)
{
	struct arswitch_softc *sc = device_get_softc(dev);
	uint16_t page;

	page = (addr >> 9) & 0x1ff;
	*phy = (addr >> 6) & 0x7;
	*reg = (addr >> 1) & 0x1f;

	if (sc->page != page) {
		MDIO_WRITEREG(device_get_parent(dev), 0x18, 0, page);
		DELAY(2000);
		sc->page = page;
	}
}
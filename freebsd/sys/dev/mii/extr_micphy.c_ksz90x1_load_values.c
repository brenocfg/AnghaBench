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
struct mii_softc {scalar_t__ mii_mpd_model; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 scalar_t__ MII_MODEL_MICREL_KSZ9031 ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int PS_TO_REG (int /*<<< orphan*/ ) ; 
 int ksz9021_read (struct mii_softc*,int) ; 
 int /*<<< orphan*/  ksz9021_write (struct mii_softc*,int,int) ; 
 int ksz9031_read (struct mii_softc*,int,int) ; 
 int /*<<< orphan*/  ksz9031_write (struct mii_softc*,int,int,int) ; 

__attribute__((used)) static void
ksz90x1_load_values(struct mii_softc *sc, phandle_t node,
    uint32_t dev, uint32_t reg, char *field1, uint32_t f1mask, int f1off,
    char *field2, uint32_t f2mask, int f2off, char *field3, uint32_t f3mask,
    int f3off, char *field4, uint32_t f4mask, int f4off)
{
	pcell_t dts_value[1];
	int len;
	int val;

	if (sc->mii_mpd_model == MII_MODEL_MICREL_KSZ9031)
		val = ksz9031_read(sc, dev, reg);
	else
		val = ksz9021_read(sc, reg);

	if ((len = OF_getproplen(node, field1)) > 0) {
		OF_getencprop(node, field1, dts_value, len);
		val &= ~(f1mask << f1off);
		val |= (PS_TO_REG(dts_value[0]) & f1mask) << f1off;
	}

	if (field2 != NULL && (len = OF_getproplen(node, field2)) > 0) {
		OF_getencprop(node, field2, dts_value, len);
		val &= ~(f2mask << f2off);
		val |= (PS_TO_REG(dts_value[0]) & f2mask) << f2off;
	}

	if (field3 != NULL && (len = OF_getproplen(node, field3)) > 0) {
		OF_getencprop(node, field3, dts_value, len);
		val &= ~(f3mask << f3off);
		val |= (PS_TO_REG(dts_value[0]) & f3mask) << f3off;
	}

	if (field4 != NULL && (len = OF_getproplen(node, field4)) > 0) {
		OF_getencprop(node, field4, dts_value, len);
		val &= ~(f4mask << f4off);
		val |= (PS_TO_REG(dts_value[0]) & f4mask) << f4off;
	}

	if (sc->mii_mpd_model == MII_MODEL_MICREL_KSZ9031)
		ksz9031_write(sc, dev, reg, val);
	else
		ksz9021_write(sc, reg, val);
}
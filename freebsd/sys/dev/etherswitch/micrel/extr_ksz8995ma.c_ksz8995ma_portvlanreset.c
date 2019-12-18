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
struct ksz8995ma_softc {int numports; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ KSZ8995MA_PC1_BASE ; 
 int KSZ8995MA_PORT_SIZE ; 
 struct ksz8995ma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ksz8995ma_readreg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ksz8995ma_writereg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void 
ksz8995ma_portvlanreset(device_t dev)
{
	int i, data;
	struct ksz8995ma_softc *sc;

	sc = device_get_softc(dev);

	for (i = 0; i < sc->numports; ++i) {
		data = ksz8995ma_readreg(dev, KSZ8995MA_PC1_BASE +
		    KSZ8995MA_PORT_SIZE * i);
		ksz8995ma_writereg(dev, KSZ8995MA_PC1_BASE +
		    KSZ8995MA_PORT_SIZE * i, (data & 0xe0) | 0x1f);
	}
}
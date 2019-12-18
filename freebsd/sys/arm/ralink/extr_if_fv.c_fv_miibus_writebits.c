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
struct fv_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_MIIMNG ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fv_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MII_CLK ; 
 int MII_DOUT ; 
 int MII_WR ; 

__attribute__((used)) static int
fv_miibus_writebits(struct fv_softc *sc, int data, int count)
{
	int bit;

	while(count--) {
		bit = ((data) >> count) & 0x1 ? MII_DOUT : 0;
		CSR_WRITE_4(sc, CSR_MIIMNG, bit | MII_WR);
		DELAY(10);
		CSR_WRITE_4(sc, CSR_MIIMNG, bit | MII_WR | MII_CLK);
		DELAY(10);
	}

	return (0);
}
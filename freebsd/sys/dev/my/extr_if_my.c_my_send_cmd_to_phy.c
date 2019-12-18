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
struct my_softc {int my_phy_addr; } ;

/* Variables and functions */
 long CSR_READ_4 (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct my_softc*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int /*<<< orphan*/  MY_MANAGEMENT ; 
 long MY_MASK_MIIR_MII_MDC ; 
 long MY_MASK_MIIR_MII_MDO ; 
 long MY_MASK_MIIR_MII_WRITE ; 
 int MY_OP_READ ; 

__attribute__((used)) static long
my_send_cmd_to_phy(struct my_softc * sc, int opcode, int regad)
{
	long            miir;
	int             i;
	int             mask, data;

	MY_LOCK_ASSERT(sc);

	/* enable MII output */
	miir = CSR_READ_4(sc, MY_MANAGEMENT);
	miir &= 0xfffffff0;

	miir |= MY_MASK_MIIR_MII_WRITE + MY_MASK_MIIR_MII_MDO;

	/* send 32 1's preamble */
	for (i = 0; i < 32; i++) {
		/* low MDC; MDO is already high (miir) */
		miir &= ~MY_MASK_MIIR_MII_MDC;
		CSR_WRITE_4(sc, MY_MANAGEMENT, miir);

		/* high MDC */
		miir |= MY_MASK_MIIR_MII_MDC;
		CSR_WRITE_4(sc, MY_MANAGEMENT, miir);
	}

	/* calculate ST+OP+PHYAD+REGAD+TA */
	data = opcode | (sc->my_phy_addr << 7) | (regad << 2);

	/* sent out */
	mask = 0x8000;
	while (mask) {
		/* low MDC, prepare MDO */
		miir &= ~(MY_MASK_MIIR_MII_MDC + MY_MASK_MIIR_MII_MDO);
		if (mask & data)
			miir |= MY_MASK_MIIR_MII_MDO;

		CSR_WRITE_4(sc, MY_MANAGEMENT, miir);
		/* high MDC */
		miir |= MY_MASK_MIIR_MII_MDC;
		CSR_WRITE_4(sc, MY_MANAGEMENT, miir);
		DELAY(30);

		/* next */
		mask >>= 1;
		if (mask == 0x2 && opcode == MY_OP_READ)
			miir &= ~MY_MASK_MIIR_MII_WRITE;
	}

	return miir;
}
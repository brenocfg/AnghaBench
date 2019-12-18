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
typedef  int uint8_t ;
struct ncr53c9x_softc {scalar_t__ sc_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NCR_FIFO ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR_MSGS (char*) ; 
 int NCR_SHOWMSGS ; 
 scalar_t__ NCR_VARIANT_FAS366 ; 
 int /*<<< orphan*/  NCR_WRITE_REG (struct ncr53c9x_softc*,int /*<<< orphan*/ ,int) ; 
 int ncr53c9x_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ncr53c9x_wrfifo(struct ncr53c9x_softc *sc, uint8_t *p, int len)
{
	int i;

	NCR_LOCK_ASSERT(sc, MA_OWNED);

#ifdef NCR53C9X_DEBUG
	NCR_MSGS(("[wrfifo(%d):", len));
	if ((ncr53c9x_debug & NCR_SHOWMSGS) != 0) {
		for (i = 0; i < len; i++)
			printf(" %02x", p[i]);
		printf("]\n");
	}
#endif

	for (i = 0; i < len; i++) {
		NCR_WRITE_REG(sc, NCR_FIFO, p[i]);

		if (sc->sc_rev == NCR_VARIANT_FAS366)
			NCR_WRITE_REG(sc, NCR_FIFO, 0);
	}
}
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
struct exca_softc {int memalloc; int ioalloc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXCA_ADDRWIN_ENABLE ; 
 int /*<<< orphan*/  EXCA_INTR ; 
 int /*<<< orphan*/  EXCA_INTR_CARDTYPE_IO ; 
 int /*<<< orphan*/  EXCA_INTR_ENABLE ; 
 int /*<<< orphan*/  EXCA_INTR_RESET ; 
 int EXCA_IO_WINS ; 
 int EXCA_MEM_WINS ; 
 int /*<<< orphan*/  EXCA_PWRCTL ; 
 int /*<<< orphan*/  EXCA_PWRCTL_OE ; 
 int /*<<< orphan*/  exca_do_io_map (struct exca_softc*,int) ; 
 int /*<<< orphan*/  exca_do_mem_map (struct exca_softc*,int) ; 
 int /*<<< orphan*/  exca_putb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_setb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_wait_ready (struct exca_softc*) ; 

void
exca_reset(struct exca_softc *sc, device_t child)
{
	int win;

	/* enable socket i/o */
	exca_setb(sc, EXCA_PWRCTL, EXCA_PWRCTL_OE);

	exca_putb(sc, EXCA_INTR, EXCA_INTR_ENABLE);
	/* hold reset for 30ms */
	DELAY(30*1000);
	/* clear the reset flag */
	exca_setb(sc, EXCA_INTR, EXCA_INTR_RESET);
	/* wait 20ms as per PC Card standard (r2.01) section 4.3.6 */
	DELAY(20*1000);

	exca_wait_ready(sc);

	/* disable all address windows */
	exca_putb(sc, EXCA_ADDRWIN_ENABLE, 0);

	exca_setb(sc, EXCA_INTR, EXCA_INTR_CARDTYPE_IO);
	DEVPRINTF(sc->dev, "card type is io\n");

	/* reinstall all the memory and io mappings */
	for (win = 0; win < EXCA_MEM_WINS; ++win)
		if (sc->memalloc & (1 << win))
			exca_do_mem_map(sc, win);
	for (win = 0; win < EXCA_IO_WINS; ++win)
		if (sc->ioalloc & (1 << win))
			exca_do_io_map(sc, win);
}
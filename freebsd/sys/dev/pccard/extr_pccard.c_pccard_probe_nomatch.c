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
struct TYPE_2__ {int manufacturer; int product; int /*<<< orphan*/ ** cis1_info; } ;
struct pccard_softc {TYPE_1__ card; } ;
struct pccard_ivar {struct pccard_function* pf; } ;
struct pccard_function {int function; int number; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 struct pccard_softc* PCCARD_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
pccard_probe_nomatch(device_t bus, device_t child)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct pccard_function *pf = devi->pf;
	struct pccard_softc *sc = PCCARD_SOFTC(bus);
	int i;

	device_printf(bus, "<unknown card>");
	printf(" (manufacturer=0x%04x, product=0x%04x, function_type=%d) "
	    "at function %d\n", sc->card.manufacturer, sc->card.product,
	    pf->function, pf->number);
	device_printf(bus, "   CIS info: ");
	for (i = 0; sc->card.cis1_info[i] != NULL && i < 4; i++)
		printf("%s%s", i > 0 ? ", " : "", sc->card.cis1_info[i]);
	printf("\n");
	return;
}
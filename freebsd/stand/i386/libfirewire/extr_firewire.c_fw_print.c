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
struct fwohci_softc {scalar_t__ state; int locator; int devid; int base_addr; int handle; int bus_id; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {char* dv_name; } ;

/* Variables and functions */
 scalar_t__ FWOHCI_STATE_DEAD ; 
 int MAX_OHCI ; 
 struct fwohci_softc* fwinfo ; 
 TYPE_1__ fwohci ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int
fw_print(int verbose)
{
	char line[80];
	int i, ret = 0;
	struct fwohci_softc *sc;

	printf("%s devices:", fwohci.dv_name);
	if ((ret = pager_output("\n")) != 0)
		return (ret);

	for (i = 0; i < MAX_OHCI; i ++) {
		sc = &fwinfo[i];
		if (sc->state == FWOHCI_STATE_DEAD)
			break;
		snprintf(line, sizeof(line), "%d: locator=0x%04x devid=0x%08x"
			" base_addr=0x%08x handle=0x%08x bus_id=0x%08x\n",
			i, sc->locator, sc->devid,
			sc->base_addr, sc->handle, sc->bus_id);
		ret = pager_output(line);
		if (ret != 0)
			break;
	}
	return (ret);
}
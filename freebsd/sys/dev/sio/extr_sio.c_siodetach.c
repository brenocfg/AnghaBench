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
struct com_s {struct com_s* ibuf; scalar_t__ ioportres; int /*<<< orphan*/  ioportrid; scalar_t__ irqres; int /*<<< orphan*/  cookie; scalar_t__ tp; int /*<<< orphan*/  gone; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct com_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyfree (scalar_t__) ; 

int
siodetach(device_t dev)
{
	struct com_s	*com;

	com = (struct com_s *) device_get_softc(dev);
	if (com == NULL) {
		device_printf(dev, "NULL com in siounload\n");
		return (0);
	}
	com->gone = TRUE;
	if (com->tp)
		ttyfree(com->tp);
	if (com->irqres) {
		bus_teardown_intr(dev, com->irqres, com->cookie);
		bus_release_resource(dev, SYS_RES_IRQ, 0, com->irqres);
	}
	if (com->ioportres)
		bus_release_resource(dev, SYS_RES_IOPORT, com->ioportrid,
				     com->ioportres);
	if (com->ibuf != NULL)
		free(com->ibuf, M_DEVBUF);

	device_set_softc(dev, NULL);
	free(com, M_DEVBUF);
	return (0);
}
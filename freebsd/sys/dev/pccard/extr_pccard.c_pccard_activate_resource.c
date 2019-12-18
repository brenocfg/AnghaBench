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
struct resource {int dummy; } ;
struct pccard_ivar {struct pccard_function* pf; } ;
struct pccard_function {int /*<<< orphan*/  sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
#define  SYS_RES_IOPORT 128 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  pccard_mfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pccard_mfc_adjust_iobase (struct pccard_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 

__attribute__((used)) static int
pccard_activate_resource(device_t brdev, device_t child, int type, int rid,
    struct resource *r)
{
	struct pccard_ivar *ivar = PCCARD_IVAR(child);
	struct pccard_function *pf = ivar->pf;

	switch(type) {
	case SYS_RES_IOPORT:
		/*
		 * We need to adjust IOBASE[01] and IOSIZE if we're an MFC
		 * card.
		 */
		if (pccard_mfc(pf->sc))
			pccard_mfc_adjust_iobase(pf, rman_get_start(r), 0,
			    rman_get_size(r));
		break;
	default:
		break;
	}
	return (bus_generic_activate_resource(brdev, child, type, rid, r));
}
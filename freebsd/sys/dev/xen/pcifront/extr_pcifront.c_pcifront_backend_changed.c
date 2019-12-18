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
struct xenbus_device {int /*<<< orphan*/  nodename; struct pcifront_device* data; } ;
struct pcifront_device {int dummy; } ;
typedef  int XenbusState ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
#define  XenbusStateClosed 130 
#define  XenbusStateClosing 129 
#define  XenbusStateConnected 128 
 int /*<<< orphan*/  pcifront_connect (struct pcifront_device*) ; 
 int /*<<< orphan*/  pcifront_disconnect (struct pcifront_device*) ; 

__attribute__((used)) static void
pcifront_backend_changed(struct xenbus_device *xdev,
						 XenbusState be_state)
{
	struct pcifront_device *pdev = xdev->data;

	switch (be_state) {
	case XenbusStateClosing:
		DPRINTF("backend closing (%s)\n", xdev->nodename);
		pcifront_disconnect(pdev);
		break;

	case XenbusStateClosed:
		DPRINTF("backend closed (%s)\n", xdev->nodename);
		pcifront_disconnect(pdev);
		break;

	case XenbusStateConnected:
		DPRINTF("backend connected (%s)\n", xdev->nodename);
		pcifront_connect(pdev);
		break;
		
	default:
		break;
	}
}
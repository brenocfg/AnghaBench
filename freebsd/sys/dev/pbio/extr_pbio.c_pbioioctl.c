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
typedef  int u_long ;
struct thread {int dummy; } ;
struct pbio_softc {TYPE_1__* pd; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int diff; int ipace; int opace; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
#define  PBIO_GETDIFF 133 
#define  PBIO_GETIPACE 132 
#define  PBIO_GETOPACE 131 
#define  PBIO_SETDIFF 130 
#define  PBIO_SETIPACE 129 
#define  PBIO_SETOPACE 128 
 int PORT (struct cdev*) ; 
 int UNIT (struct cdev*) ; 
 struct pbio_softc* pbio_addr (int) ; 

__attribute__((used)) static int
pbioioctl (struct cdev *dev, u_long cmd, caddr_t data, int flag,
    struct thread *td)
{
	struct pbio_softc *scp;
	int port, unit;
	
	unit = UNIT(dev);
	port = PORT(dev);
	scp = pbio_addr(unit);
	if (scp == NULL)
		return (ENODEV);
	switch (cmd) {
	case PBIO_SETDIFF:
		scp->pd[port].diff = *(int *)data;
		break;
	case PBIO_SETIPACE:
		scp->pd[port].ipace = *(int *)data;
		break;
	case PBIO_SETOPACE:
		scp->pd[port].opace = *(int *)data;
		break;
	case PBIO_GETDIFF:
		*(int *)data = scp->pd[port].diff;
		break;
	case PBIO_GETIPACE:
		*(int *)data = scp->pd[port].ipace;
		break;
	case PBIO_GETOPACE:
		*(int *)data = scp->pd[port].opace;
		break;
	default:
		return ENXIO;
	}
	return (0);
}
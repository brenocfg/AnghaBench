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
struct uio {scalar_t__ uio_resid; } ;
struct pbio_softc {TYPE_1__* pd; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {char* buff; scalar_t__ opace; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PBIOPRI ; 
 int /*<<< orphan*/  PBIO_BUFSIZ ; 
 int /*<<< orphan*/  PBIO_PORTA ; 
 int /*<<< orphan*/  PBIO_PORTB ; 
 int /*<<< orphan*/  PBIO_PORTC ; 
 int PORT (struct cdev*) ; 
 int UNIT (struct cdev*) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 char pbinb (struct pbio_softc*,int /*<<< orphan*/ ) ; 
 struct pbio_softc* pbio_addr (int) ; 
 int /*<<< orphan*/  pboutb (struct pbio_softc*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int uiomove (char*,int,struct uio*) ; 

__attribute__((used)) static int
pbiowrite(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct pbio_softc *scp;
	int i, port, ret, towrite, unit;
	char val, oval;
	
	unit = UNIT(dev);
	port = PORT(dev);
	scp = pbio_addr(unit);
	if (scp == NULL)
		return (ENODEV);

	while (uio->uio_resid > 0) {
		towrite = min(uio->uio_resid, PBIO_BUFSIZ);
		if ((ret = uiomove(scp->pd[port].buff, towrite, uio)) != 0)
			return (ret);
		for (i = 0; i < towrite; i++) {
			val = scp->pd[port].buff[i];
			switch (port) {
			case 0:
				pboutb(scp, PBIO_PORTA, val);
				break;
			case 1:
				pboutb(scp, PBIO_PORTB, val);
				break;
			case 2:
				oval = pbinb(scp, PBIO_PORTC);
				oval &= 0xf;
				val <<= 4;
				pboutb(scp, PBIO_PORTC, val | oval);
				break;
			case 3:
				oval = pbinb(scp, PBIO_PORTC);
				oval &= 0xf0;
				val &= 0xf;
				pboutb(scp, PBIO_PORTC, oval | val);
				break;
			}
			if (scp->pd[port].opace)
				tsleep((caddr_t)&(scp->pd[port].opace),
					PBIOPRI, "pbioop",
					scp->pd[port].opace);
		}
	}
	return (0);
}
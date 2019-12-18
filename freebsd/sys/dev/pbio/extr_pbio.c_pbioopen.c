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
struct thread {int dummy; } ;
struct pbio_softc {int iomode; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  PBIO_CFG ; 
 int PORT (struct cdev*) ; 
 int UNIT (struct cdev*) ; 
 struct pbio_softc* pbio_addr (int) ; 
 int /*<<< orphan*/  pboutb (struct pbio_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static  int
pbioopen(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct pbio_softc *scp;
	int ocfg, port, unit;
	int portbit;			/* Port configuration bit */
	
	unit = UNIT(dev);
	port = PORT(dev);
	scp = pbio_addr(unit);
	if (scp == NULL)
		return (ENODEV);
	
	switch (port) {
	case 0: portbit = 0x10; break;	/* Port A */
	case 1: portbit = 0x02; break;	/* Port B */
	case 2: portbit = 0x08; break;	/* Port CH */
	case 3: portbit = 0x01; break;	/* Port CL */
	default: return (ENODEV);
	}
	ocfg = scp->iomode;

	if (oflags & FWRITE)
		/* Writing == output; zero the bit */
		pboutb(scp, PBIO_CFG, scp->iomode = (ocfg & (~portbit)));
	else if (oflags & FREAD)
		/* Reading == input; set the bit */
		pboutb(scp, PBIO_CFG, scp->iomode = (ocfg | portbit));
	else
		return (EACCES);

	return (0);
}
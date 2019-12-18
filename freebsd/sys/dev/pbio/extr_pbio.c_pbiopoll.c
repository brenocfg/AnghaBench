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
struct pbio_softc {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int UNIT (struct cdev*) ; 
 struct pbio_softc* pbio_addr (int) ; 

__attribute__((used)) static  int
pbiopoll(struct cdev *dev, int which, struct thread *td)
{
	struct pbio_softc *scp;
	int unit;
	
	unit = UNIT(dev);
	scp = pbio_addr(unit);
	if (scp == NULL)
		return (ENODEV);
	
	/*
	 * Do processing
	 */
	return (0); /* this is the wrong value I'm sure */
}
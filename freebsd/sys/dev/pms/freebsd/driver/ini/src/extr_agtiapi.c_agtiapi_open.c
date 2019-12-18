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
struct cdev {struct agtiapi_softc* si_drv1; } ;
struct agtiapi_softc {int /*<<< orphan*/  my_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGTIAPI_PRINTK (char*,...) ; 

int agtiapi_open( struct cdev *dev, int oflags, int devtype, struct thread *td )
{
  struct agtiapi_softc *sc;
  /* Look up our softc. */
  sc = dev->si_drv1;
  AGTIAPI_PRINTK("agtiapi_open\n");
  AGTIAPI_PRINTK("Opened successfully. sc->my_dev %p\n", sc->my_dev);
  return( 0 );
}
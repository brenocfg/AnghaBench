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
struct cdev {int dummy; } ;
struct bktr_softc {scalar_t__ bigbuf; } ;
typedef  scalar_t__ ioctl_cmd_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  struct bktr_softc* bktr_ptr_t ;

/* Variables and functions */
 scalar_t__ BT848_GPIO_GET_DATA ; 
 scalar_t__ BT848_GPIO_GET_EN ; 
 scalar_t__ BT848_GPIO_SET_DATA ; 
 scalar_t__ BT848_GPIO_SET_EN ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FUNCTION (int /*<<< orphan*/ ) ; 
#define  TUNER_DEV 129 
 int UNIT (int /*<<< orphan*/ ) ; 
#define  VIDEO_DEV 128 
 int /*<<< orphan*/  bktr_devclass ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int tuner_ioctl (struct bktr_softc*,int,scalar_t__,int /*<<< orphan*/ ,struct thread*) ; 
 int video_ioctl (struct bktr_softc*,int,scalar_t__,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
bktr_ioctl( struct cdev *dev, ioctl_cmd_t cmd, caddr_t arg, int flag, struct thread *td )
{
	bktr_ptr_t	bktr;
	int		unit;

	unit = UNIT(dev2unit(dev));

	/* Get the device data */
	bktr = (struct bktr_softc*)devclass_get_softc(bktr_devclass, unit);
	if (bktr == NULL) {
		/* the device is no longer valid/functioning */
		return (ENXIO);
	}

#ifdef BKTR_GPIO_ACCESS
	if (bktr->bigbuf == 0 && cmd != BT848_GPIO_GET_EN &&
	    cmd != BT848_GPIO_SET_EN && cmd != BT848_GPIO_GET_DATA &&
	    cmd != BT848_GPIO_SET_DATA)	/* no frame buffer allocated (ioctl failed) */
		return( ENOMEM );
#else
	if (bktr->bigbuf == 0)	/* no frame buffer allocated (ioctl failed) */
		return( ENOMEM );
#endif

	switch ( FUNCTION( dev2unit(dev) ) ) {
	case VIDEO_DEV:
		return( video_ioctl( bktr, unit, cmd, arg, td ) );
	case TUNER_DEV:
		return( tuner_ioctl( bktr, unit, cmd, arg, td ) );
	}

	return( ENXIO );
}
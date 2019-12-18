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
struct bktr_softc {int dummy; } ;
typedef  struct bktr_softc* bktr_ptr_t ;

/* Variables and functions */
 int ENXIO ; 
 int FUNCTION (int /*<<< orphan*/ ) ; 
#define  TUNER_DEV 130 
 int UNIT (int /*<<< orphan*/ ) ; 
#define  VBI_DEV 129 
#define  VIDEO_DEV 128 
 int /*<<< orphan*/  bktr_devclass ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int tuner_close (struct bktr_softc*) ; 
 int vbi_close (struct bktr_softc*) ; 
 int video_close (struct bktr_softc*) ; 

__attribute__((used)) static int
bktr_close( struct cdev *dev, int flags, int fmt, struct thread *td )
{
	bktr_ptr_t	bktr;
	int		unit;
	int		result;

	unit = UNIT( dev2unit(dev) );

	/* Get the device data */
	bktr = (struct bktr_softc*)devclass_get_softc(bktr_devclass, unit);
	if (bktr == NULL) {
		/* the device is no longer valid/functioning */
		return (ENXIO);
	}

	switch ( FUNCTION( dev2unit(dev) ) ) {
	case VIDEO_DEV:
		result = video_close( bktr );
		break;
	case TUNER_DEV:
		result = tuner_close( bktr );
		break;
	case VBI_DEV:
		result = vbi_close( bktr );
		break;
	default:
		return (ENXIO);
		break;
	}

	device_unbusy(devclass_get_device(bktr_devclass, unit)); 
	return( result );
}
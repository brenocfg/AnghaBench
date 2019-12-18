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
struct uio {int dummy; } ;
struct cdev {int dummy; } ;
struct bktr_softc {int dummy; } ;
typedef  struct bktr_softc* bktr_ptr_t ;

/* Variables and functions */
 int ENXIO ; 
 int FUNCTION (int /*<<< orphan*/ ) ; 
 int UNIT (int /*<<< orphan*/ ) ; 
#define  VBI_DEV 129 
#define  VIDEO_DEV 128 
 int /*<<< orphan*/  bktr_devclass ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int vbi_read (struct bktr_softc*,struct uio*,int) ; 
 int video_read (struct bktr_softc*,int,struct cdev*,struct uio*) ; 

__attribute__((used)) static int
bktr_read( struct cdev *dev, struct uio *uio, int ioflag )
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

	switch ( FUNCTION( dev2unit(dev) ) ) {
	case VIDEO_DEV:
		return( video_read( bktr, unit, dev, uio ) );
	case VBI_DEV:
		return( vbi_read( bktr, uio, ioflag ) );
	}
        return( ENXIO );
}
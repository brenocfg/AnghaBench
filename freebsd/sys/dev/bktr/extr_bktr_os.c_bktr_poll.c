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
struct bktr_softc {int /*<<< orphan*/  vbi_select; int /*<<< orphan*/  vbisize; } ;
typedef  struct bktr_softc* bktr_ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_INTR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISABLE_INTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENABLE_INTR (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_VBI (struct bktr_softc*) ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK_VBI (struct bktr_softc*) ; 
#define  VBI_DEV 128 
 int /*<<< orphan*/  bktr_devclass ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bktr_poll( struct cdev *dev, int events, struct thread *td)
{
	int		unit;
	bktr_ptr_t	bktr;
	int revents = 0; 
	DECLARE_INTR_MASK(s);

	unit = UNIT(dev2unit(dev));

	/* Get the device data */
	bktr = (struct bktr_softc*)devclass_get_softc(bktr_devclass, unit);
	if (bktr == NULL) {
		/* the device is no longer valid/functioning */
		return (ENXIO);
	}

	LOCK_VBI(bktr);
	DISABLE_INTR(s);

	if (events & (POLLIN | POLLRDNORM)) {

		switch ( FUNCTION( dev2unit(dev) ) ) {
		case VBI_DEV:
			if(bktr->vbisize == 0)
				selrecord(td, &bktr->vbi_select);
			else
				revents |= events & (POLLIN | POLLRDNORM);
			break;
		}
	}

	ENABLE_INTR(s);
	UNLOCK_VBI(bktr);

	return (revents);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mps_softc {scalar_t__ recorded_events; } ;
struct TYPE_3__ {int Size; int /*<<< orphan*/  PtrEvents; } ;
typedef  TYPE_1__ mps_event_report_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 scalar_t__ copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mps_lock (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_unlock (struct mps_softc*) ; 

__attribute__((used)) static int
mps_user_event_report(struct mps_softc *sc, mps_event_report_t *data)
{
	int		status = 0;
	uint32_t	size;

	mps_lock(sc);
	size = data->Size;
	if ((size >= sizeof(sc->recorded_events)) && (status == 0)) {
		mps_unlock(sc);
		if (copyout((void *)sc->recorded_events,
		    PTRIN(data->PtrEvents), size) != 0)
			status = EFAULT;
		mps_lock(sc);
	} else {
		/*
		 * data->Size value is not large enough to copy event data.
		 */
		status = EFAULT;
	}

	/*
	 * Change size value to match the number of bytes that were copied.
	 */
	if (status == 0)
		data->Size = sizeof(sc->recorded_events);
	mps_unlock(sc);

	return (status);
}
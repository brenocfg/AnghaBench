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
typedef  size_t uint32_t ;
struct ioat_softc {int /*<<< orphan*/  dmaengine; int /*<<< orphan*/  submit_lock; scalar_t__ destroying; scalar_t__ quiescing; } ;
typedef  int /*<<< orphan*/ * bus_dmaengine_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 struct ioat_softc** ioat_channel ; 
 size_t ioat_channel_index ; 
 int /*<<< orphan*/  ioat_get (struct ioat_softc*) ; 
 int /*<<< orphan*/  ioat_list_mtx ; 
 int /*<<< orphan*/  ioat_put (struct ioat_softc*) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

bus_dmaengine_t
ioat_get_dmaengine(uint32_t index, int flags)
{
	struct ioat_softc *ioat;

	KASSERT((flags & ~(M_NOWAIT | M_WAITOK)) == 0,
	    ("invalid flags: 0x%08x", flags));
	KASSERT((flags & (M_NOWAIT | M_WAITOK)) != (M_NOWAIT | M_WAITOK),
	    ("invalid wait | nowait"));

	mtx_lock(&ioat_list_mtx);
	if (index >= ioat_channel_index ||
	    (ioat = ioat_channel[index]) == NULL) {
		mtx_unlock(&ioat_list_mtx);
		return (NULL);
	}
	mtx_lock(&ioat->submit_lock);
	mtx_unlock(&ioat_list_mtx);

	if (ioat->destroying) {
		mtx_unlock(&ioat->submit_lock);
		return (NULL);
	}

	ioat_get(ioat);
	if (ioat->quiescing) {
		if ((flags & M_NOWAIT) != 0) {
			ioat_put(ioat);
			mtx_unlock(&ioat->submit_lock);
			return (NULL);
		}

		while (ioat->quiescing && !ioat->destroying)
			msleep(&ioat->quiescing, &ioat->submit_lock, 0, "getdma", 0);

		if (ioat->destroying) {
			ioat_put(ioat);
			mtx_unlock(&ioat->submit_lock);
			return (NULL);
		}
	}
	mtx_unlock(&ioat->submit_lock);
	return (&ioat->dmaengine);
}
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
struct siis_channel {int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siis_ch_intr (void*) ; 

__attribute__((used)) static void
siis_ch_intr_locked(void *data)
{
	device_t dev = (device_t)data;
	struct siis_channel *ch = device_get_softc(dev);

	mtx_lock(&ch->mtx);
	siis_ch_intr(data);
	mtx_unlock(&ch->mtx);
}
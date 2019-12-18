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
typedef  int u_int ;
struct davbus_softc {int (* read_status ) (struct davbus_softc*,int) ;int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg; int /*<<< orphan*/  (* set_outputs ) (struct davbus_softc*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DAVBUS_CODEC_STATUS ; 
 int DAVBUS_PORTCHG ; 
 int /*<<< orphan*/  DAVBUS_SOUND_CTRL ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct davbus_softc*,int) ; 
 int /*<<< orphan*/  stub2 (struct davbus_softc*,int) ; 

__attribute__((used)) static void 
davbus_cint(void *ptr)
{
	struct davbus_softc *d = ptr;
	u_int	reg, status, mask;

	mtx_lock(&d->mutex);

	reg = bus_read_4(d->reg, DAVBUS_SOUND_CTRL);
	if (reg & DAVBUS_PORTCHG) {
		
		status = bus_read_4(d->reg, DAVBUS_CODEC_STATUS);
		
		if (d->read_status && d->set_outputs) {

			mask = (*d->read_status)(d, status);
			(*d->set_outputs)(d, mask);
		}

		/* Clear the interrupt. */
		bus_write_4(d->reg, DAVBUS_SOUND_CTRL, reg);
	}

	mtx_unlock(&d->mutex);
}
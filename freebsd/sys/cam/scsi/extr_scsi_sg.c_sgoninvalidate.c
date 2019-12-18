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
struct sg_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_FLAG_INVALID ; 
 int /*<<< orphan*/  destroy_dev_sched_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_periph*) ; 
 int /*<<< orphan*/  sgasync ; 
 int /*<<< orphan*/  sgdevgonecb ; 
 int /*<<< orphan*/  xpt_register_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sgoninvalidate(struct cam_periph *periph)
{
	struct sg_softc *softc;

	softc = (struct sg_softc *)periph->softc;

	/*
	 * Deregister any async callbacks.
	 */
	xpt_register_async(0, sgasync, periph, periph->path);

	softc->flags |= SG_FLAG_INVALID;

	/*
	 * Tell devfs this device has gone away, and ask for a callback
	 * when it has cleaned up its state.
	 */
	destroy_dev_sched_cb(softc->dev, sgdevgonecb, periph);

	/*
	 * XXX Return all queued I/O with ENXIO.
	 * XXX Handle any transactions queued to the card
	 *     with XPT_ABORT_CCB.
	 */

}
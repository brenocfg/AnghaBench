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
struct cd_softc {int /*<<< orphan*/  disk; int /*<<< orphan*/  bio_queue; int /*<<< orphan*/  flags; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_FLAG_INVALID ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  bioq_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdasync ; 
 int /*<<< orphan*/  disk_gone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_register_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdoninvalidate(struct cam_periph *periph)
{
	struct cd_softc *softc;

	softc = (struct cd_softc *)periph->softc;

	/*
	 * De-register any async callbacks.
	 */
	xpt_register_async(0, cdasync, periph, periph->path);

	softc->flags |= CD_FLAG_INVALID;

	/*
	 * Return all queued I/O with ENXIO.
	 * XXX Handle any transactions queued to the card
	 *     with XPT_ABORT_CCB.
	 */
	bioq_flush(&softc->bio_queue, NULL, ENXIO);

	disk_gone(softc->disk);
}
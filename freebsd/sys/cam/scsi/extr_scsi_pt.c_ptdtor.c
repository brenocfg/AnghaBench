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
struct pt_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  device_stats; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptdtor(struct cam_periph *periph)
{
	struct pt_softc *softc;

	softc = (struct pt_softc *)periph->softc;

	devstat_remove_entry(softc->device_stats);
	cam_periph_unlock(periph);
	destroy_dev(softc->dev);
	cam_periph_lock(periph);
	free(softc, M_DEVBUF);
}
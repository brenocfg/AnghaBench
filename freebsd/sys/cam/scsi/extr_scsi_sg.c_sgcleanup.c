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
struct sg_softc {int /*<<< orphan*/  device_stats; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sg_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sgcleanup(struct cam_periph *periph)
{
	struct sg_softc *softc;

	softc = (struct sg_softc *)periph->softc;

	devstat_remove_entry(softc->device_stats);

	free(softc, M_DEVBUF);
}
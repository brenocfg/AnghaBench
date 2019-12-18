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
typedef  int /*<<< orphan*/  u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
ahd_add_scb_to_free_list(struct ahd_softc *ahd, u_int scbid)
{
/* XXX Need some other mechanism to designate "free". */
	/*
	 * Invalidate the tag so that our abort
	 * routines don't think it's active.
	ahd_outb(ahd, SCB_TAG, SCB_LIST_NULL);
	 */
}
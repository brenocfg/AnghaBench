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
 int /*<<< orphan*/  ahd_index_busy_tcl (struct ahd_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int /*<<< orphan*/ ) ; 

void
ahd_busy_tcl(struct ahd_softc *ahd, u_int tcl, u_int scbid)
{
	u_int scb_offset;
	u_int saved_scbptr;
		
	scb_offset = ahd_index_busy_tcl(ahd, &saved_scbptr, tcl);
	ahd_outw(ahd, scb_offset, scbid);
	ahd_set_scbptr(ahd, saved_scbptr);
}
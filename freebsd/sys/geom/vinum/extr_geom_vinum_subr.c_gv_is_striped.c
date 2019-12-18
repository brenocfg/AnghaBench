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
struct gv_plex {int org; } ;

/* Variables and functions */
#define  GV_PLEX_RAID5 129 
#define  GV_PLEX_STRIPED 128 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

int
gv_is_striped(struct gv_plex *p)
{
	KASSERT(p != NULL, ("gv_is_striped: NULL p"));
	switch(p->org) {
	case GV_PLEX_STRIPED:
	case GV_PLEX_RAID5:
		return (1);
	default:
		return (0);
	}
}
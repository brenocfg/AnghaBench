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
struct cam_periph {int refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camperiphfree (struct cam_periph*) ; 

void
cam_periph_release_locked_buses(struct cam_periph *periph)
{

	cam_periph_assert(periph, MA_OWNED);
	KASSERT(periph->refcount >= 1, ("periph->refcount >= 1"));
	if (--periph->refcount == 0)
		camperiphfree(periph);
}
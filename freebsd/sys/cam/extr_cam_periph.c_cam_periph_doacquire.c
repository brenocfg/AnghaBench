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
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

void
cam_periph_doacquire(struct cam_periph *periph)
{

	xpt_lock_buses();
	KASSERT(periph->refcount >= 1,
	    ("cam_periph_doacquire() with refcount == %d", periph->refcount));
	periph->refcount++;
	xpt_unlock_buses();
}
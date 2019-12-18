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
struct mtx {int dummy; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 struct mtx* cam_periph_mtx (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

void
cam_periph_release(struct cam_periph *periph)
{
	struct mtx *mtx;

	if (periph == NULL)
		return;
	
	cam_periph_assert(periph, MA_NOTOWNED);
	mtx = cam_periph_mtx(periph);
	mtx_lock(mtx);
	cam_periph_release_locked(periph);
	mtx_unlock(mtx);
}
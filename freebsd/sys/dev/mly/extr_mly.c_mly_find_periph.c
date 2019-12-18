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
struct mly_softc {int /*<<< orphan*/ * mly_cam_sim; } ;
struct cam_periph {int dummy; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int CAM_REQ_CMP ; 
 struct cam_periph* cam_periph_find (struct cam_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 

__attribute__((used)) static struct cam_periph *
mly_find_periph(struct mly_softc *sc, int bus, int target)
{
    struct cam_periph	*periph;
    struct cam_path	*path;
    int			status;

    status = xpt_create_path(&path, NULL, cam_sim_path(sc->mly_cam_sim[bus]), target, 0);
    if (status == CAM_REQ_CMP) {
	periph = cam_periph_find(path, NULL);
	xpt_free_path(path);
    } else {
	periph = NULL;
    }
    return(periph);
}
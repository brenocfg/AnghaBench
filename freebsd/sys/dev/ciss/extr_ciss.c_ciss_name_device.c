#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {TYPE_1__** ciss_logical; int /*<<< orphan*/ * ciss_cam_sim; } ;
struct cam_periph {char* periph_name; int /*<<< orphan*/  unit_number; } ;
struct cam_path {int dummy; } ;
struct TYPE_2__ {scalar_t__* cl_name; } ;

/* Variables and functions */
 int CAM_REQ_CMP ; 
 scalar_t__ CISS_IS_PHYSICAL (int) ; 
 int ENOENT ; 
 struct cam_periph* cam_periph_find (struct cam_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,char*,int /*<<< orphan*/ ) ; 
 int xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_lock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_unlock (struct cam_path*) ; 

__attribute__((used)) static int
ciss_name_device(struct ciss_softc *sc, int bus, int target)
{
    struct cam_periph	*periph;
    struct cam_path	*path;
    int			status;

    if (CISS_IS_PHYSICAL(bus))
	return (0);

    status = xpt_create_path(&path, NULL, cam_sim_path(sc->ciss_cam_sim[bus]),
			     target, 0);

    if (status == CAM_REQ_CMP) {
	xpt_path_lock(path);
	periph = cam_periph_find(path, NULL);
	xpt_path_unlock(path);
	xpt_free_path(path);
	if (periph != NULL) {
		sprintf(sc->ciss_logical[bus][target].cl_name, "%s%d",
			periph->periph_name, periph->unit_number);
		return(0);
	}
    }
    sc->ciss_logical[bus][target].cl_name[0] = 0;
    return(ENOENT);
}
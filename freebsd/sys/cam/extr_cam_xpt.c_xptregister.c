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
struct cam_sim {struct cam_periph* softc; } ;
struct cam_periph {int /*<<< orphan*/ * softc; } ;
typedef  int /*<<< orphan*/  cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct cam_periph* xpt_periph ; 

__attribute__((used)) static cam_status
xptregister(struct cam_periph *periph, void *arg)
{
	struct cam_sim *xpt_sim;

	if (periph == NULL) {
		printf("xptregister: periph was NULL!!\n");
		return(CAM_REQ_CMP_ERR);
	}

	xpt_sim = (struct cam_sim *)arg;
	xpt_sim->softc = periph;
	xpt_periph = periph;
	periph->softc = NULL;

	return(CAM_REQ_CMP);
}
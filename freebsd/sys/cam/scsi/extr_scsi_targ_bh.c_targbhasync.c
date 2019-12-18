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
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  path_id; } ;
struct ccb_pathinq {int target_sprt; TYPE_1__ ccb_h; } ;
struct cam_periph {int dummy; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  scalar_t__ cam_status ;

/* Variables and functions */
#define  AC_PATH_DEREGISTERED 129 
#define  AC_PATH_REGISTERED 128 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_PERIPH_BIO ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int PIT_PROCESSOR ; 
 scalar_t__ cam_periph_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cam_path*,void (*) (void*,int,struct cam_path*,void*),int const,struct ccb_pathinq*) ; 
 struct cam_periph* cam_periph_find (struct cam_path*,char*) ; 
 int /*<<< orphan*/  cam_periph_invalidate (struct cam_periph*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  targbhctor ; 
 int /*<<< orphan*/  targbhdtor ; 
 int /*<<< orphan*/  targbhstart ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_path_id (struct cam_path*) ; 

__attribute__((used)) static void
targbhasync(void *callback_arg, u_int32_t code,
	    struct cam_path *path, void *arg)
{
	struct cam_path *new_path;
	struct ccb_pathinq *cpi;
	path_id_t bus_path_id;
	cam_status status;

	cpi = (struct ccb_pathinq *)arg;
	if (code == AC_PATH_REGISTERED)
		bus_path_id = cpi->ccb_h.path_id;
	else
		bus_path_id = xpt_path_path_id(path);
	/*
	 * Allocate a peripheral instance for
	 * this target instance.
	 */
	status = xpt_create_path(&new_path, NULL,
				 bus_path_id,
				 CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD);
	if (status != CAM_REQ_CMP) {
		printf("targbhasync: Unable to create path "
			"due to status 0x%x\n", status);
		return;
	}

	switch (code) {
	case AC_PATH_REGISTERED:
	{
		/* Only attach to controllers that support target mode */
		if ((cpi->target_sprt & PIT_PROCESSOR) == 0)
			break;

		status = cam_periph_alloc(targbhctor, NULL, targbhdtor,
					  targbhstart,
					  "targbh", CAM_PERIPH_BIO,
					  new_path, targbhasync,
					  AC_PATH_REGISTERED,
					  cpi);
		break;
	}
	case AC_PATH_DEREGISTERED:
	{
		struct cam_periph *periph;

		if ((periph = cam_periph_find(new_path, "targbh")) != NULL)
			cam_periph_invalidate(periph);
		break;
	}
	default:
		break;
	}
	xpt_free_path(new_path);
}
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
struct pass_softc {int dummy; } ;
struct pass_io_req {int data_flags; int num_bufs; int /*<<< orphan*/ * dirs; int /*<<< orphan*/ * user_bufs; int /*<<< orphan*/ * kern_bufs; int /*<<< orphan*/ * lengths; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;

/* Variables and functions */
#define  CAM_DATA_BIO 132 
#define  CAM_DATA_PADDR 131 
#define  CAM_DATA_SG 130 
#define  CAM_DATA_SG_PADDR 129 
#define  CAM_DATA_VADDR 128 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int EINVAL ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int passcopysglist (struct cam_periph*,struct pass_io_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  passiocleanup (struct pass_softc*,struct pass_io_req*) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
passmemdone(struct cam_periph *periph, struct pass_io_req *io_req)
{
	struct pass_softc *softc;
	int error;
	int i;

	error = 0;
	softc = (struct pass_softc *)periph->softc;

	switch (io_req->data_flags) {
	case CAM_DATA_VADDR:
		/*
		 * Copy back to the user buffer if this was a read.
		 */
		for (i = 0; i < io_req->num_bufs; i++) {
			if (io_req->dirs[i] != CAM_DIR_IN)
				continue;

			error = copyout(io_req->kern_bufs[i],
			    io_req->user_bufs[i], io_req->lengths[i]);
			if (error != 0) {
				xpt_print(periph->path, "Unable to copy %u "
					  "bytes from %p to user address %p\n",
					  io_req->lengths[i],
					  io_req->kern_bufs[i],
					  io_req->user_bufs[i]);
				goto bailout;
			}

		}
		break;
	case CAM_DATA_PADDR:
		/* Do nothing.  The pointer is a physical address already */
		break;
	case CAM_DATA_SG:
		/*
		 * Copy back to the user buffer if this was a read.
		 * Restore the user's S/G list buffer pointer.
		 */
		if (io_req->dirs[0] == CAM_DIR_IN)
			error = passcopysglist(periph, io_req, io_req->dirs[0]);
		break;
	case CAM_DATA_SG_PADDR:
		/*
		 * Restore the user's S/G list buffer pointer.  No need to
		 * copy.
		 */
		break;
	default:
	case CAM_DATA_BIO:
		error = EINVAL;
		break;
	}

bailout:
	/*
	 * Reset the user's pointers to their original values and free
	 * allocated memory.
	 */
	passiocleanup(softc, io_req);

	return (error);
}
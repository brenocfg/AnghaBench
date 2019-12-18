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
typedef  union ccb {int dummy; } ccb ;
struct ccb_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGIOCDEBUG ; 
 int /*<<< orphan*/  TARGIOCDISABLE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  free_ccb (union ccb*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int kq_fd ; 
 int /*<<< orphan*/  pending_queue ; 
 TYPE_1__ periph_links ; 
 int targ_fd ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  work_queue ; 

__attribute__((used)) static void
cleanup()
{
	struct ccb_hdr *ccb_h;

	if (debug) {
		warnx("cleanup called");
		debug = 0;
		ioctl(targ_fd, TARGIOCDEBUG, &debug);
	}
	ioctl(targ_fd, TARGIOCDISABLE, NULL);
	close(targ_fd);

	while ((ccb_h = TAILQ_FIRST(&pending_queue)) != NULL) {
		TAILQ_REMOVE(&pending_queue, ccb_h, periph_links.tqe);
		free_ccb((union ccb *)ccb_h);
	}
	while ((ccb_h = TAILQ_FIRST(&work_queue)) != NULL) {
		TAILQ_REMOVE(&work_queue, ccb_h, periph_links.tqe);
		free_ccb((union ccb *)ccb_h);
	}

	if (kq_fd != -1)
		close(kq_fd);
}
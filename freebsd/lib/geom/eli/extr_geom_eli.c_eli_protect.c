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
struct rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCL_FUTURE ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int /*<<< orphan*/ ) ; 
 int mlockall (int /*<<< orphan*/ ) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eli_protect(struct gctl_req *req)
{
	struct rlimit rl;

	/* Disable core dumps. */
	rl.rlim_cur = 0;
	rl.rlim_max = 0;
	if (setrlimit(RLIMIT_CORE, &rl) == -1) {
		gctl_error(req, "Cannot disable core dumps: %s.",
		    strerror(errno));
		return (-1);
	}
	/* Disable swapping. */
	if (mlockall(MCL_FUTURE) == -1) {
		gctl_error(req, "Cannot lock memory: %s.", strerror(errno));
		return (-1);
	}
	return (0);
}
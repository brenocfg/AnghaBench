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
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 

__attribute__((used)) static int
g_sched_get_nargs(struct gctl_req *req)
{
	int *nargs;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No 'nargs' argument");
		return (0);
	}
	if (*nargs <= 0)
		gctl_error(req, "Missing device(s).");
	return (*nargs);
}
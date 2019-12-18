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
struct gctl_req_arg {int /*<<< orphan*/  name; } ;
struct gctl_req {unsigned int narg; struct gctl_req_arg* arg; int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
gctl_has_param(struct gctl_req *req, const char *name)
{
	struct gctl_req_arg *ap;
	unsigned int i;

	if (req == NULL || req->error != NULL)
		return (0);

	for (i = 0; i < req->narg; i++) {
		ap = &req->arg[i];
		if (strcmp(ap->name, name) == 0)
			return (1);
	}
	return (0);
}
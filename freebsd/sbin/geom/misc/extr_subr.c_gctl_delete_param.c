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
 int EDOOFUS ; 
 int ENOENT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
gctl_delete_param(struct gctl_req *req, const char *name)
{
	struct gctl_req_arg *ap;
	unsigned int i;

	if (req == NULL || req->error != NULL)
		return (EDOOFUS);

	i = 0;
	while (i < req->narg) {
		ap = &req->arg[i];
		if (strcmp(ap->name, name) == 0)
			break;
		i++;
	}
	if (i == req->narg)
		return (ENOENT);

	free(ap->name);
	req->narg--;
	while (i < req->narg) {
		req->arg[i] = req->arg[i + 1];
		i++;
	}
	return (0);
}
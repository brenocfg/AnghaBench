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
typedef  size_t u_int ;
struct gctl_req_arg {int flag; int len; int /*<<< orphan*/  kvalue; int /*<<< orphan*/  name; } ;
struct gctl_req {size_t narg; struct gctl_req_arg* arg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int EPERM ; 
 int GCTL_PARAM_CHANGED ; 
 int GCTL_PARAM_WR ; 
 int /*<<< orphan*/  bcopy (void const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
gctl_set_param(struct gctl_req *req, const char *param, void const *ptr,
    int len)
{
	u_int i;
	struct gctl_req_arg *ap;

	for (i = 0; i < req->narg; i++) {
		ap = &req->arg[i];
		if (strcmp(param, ap->name))
			continue;
		if (!(ap->flag & GCTL_PARAM_WR))
			return (EPERM);
		ap->flag |= GCTL_PARAM_CHANGED;
		if (ap->len < len) {
			bcopy(ptr, ap->kvalue, ap->len);
			return (ENOSPC);
		}
		bcopy(ptr, ap->kvalue, len);
		return (0);
	}
	return (EINVAL);
}
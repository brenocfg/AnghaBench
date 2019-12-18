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
struct gctl_req_arg {int flag; int /*<<< orphan*/  len; int /*<<< orphan*/  value; int /*<<< orphan*/  kvalue; } ;
struct gctl_req {int nerror; int narg; struct gctl_req_arg* arg; } ;

/* Variables and functions */
 int GCTL_PARAM_CHANGED ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gctl_copyout(struct gctl_req *req)
{
	int error, i;
	struct gctl_req_arg *ap;

	if (req->nerror)
		return;
	error = 0;
	ap = req->arg;
	for (i = 0; i < req->narg; i++, ap++) {
		if (!(ap->flag & GCTL_PARAM_CHANGED))
			continue;
		error = copyout(ap->kvalue, ap->value, ap->len);
		if (!error)
			continue;
		req->nerror = error;
		return;
	}
	return;
}
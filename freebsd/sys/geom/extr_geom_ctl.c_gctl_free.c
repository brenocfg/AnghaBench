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
typedef  size_t u_int ;
struct gctl_req {size_t narg; TYPE_1__* arg; int /*<<< orphan*/  serror; } ;
struct TYPE_2__ {int flag; scalar_t__ len; struct TYPE_2__* kvalue; struct TYPE_2__* name; } ;

/* Variables and functions */
 int GCTL_PARAM_NAMEKERNEL ; 
 int GCTL_PARAM_VALUEKERNEL ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gctl_free(struct gctl_req *req)
{
	u_int i;

	sbuf_delete(req->serror);
	if (req->arg == NULL)
		return;
	for (i = 0; i < req->narg; i++) {
		if (req->arg[i].flag & GCTL_PARAM_NAMEKERNEL)
			g_free(req->arg[i].name);
		if ((req->arg[i].flag & GCTL_PARAM_VALUEKERNEL) &&
		    req->arg[i].len > 0)
			g_free(req->arg[i].kvalue);
	}
	g_free(req->arg);
}
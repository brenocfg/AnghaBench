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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct gctl_req {int nerror; int lerror; scalar_t__ version; int /*<<< orphan*/  serror; int /*<<< orphan*/  error; int /*<<< orphan*/ * arg; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GCTL_VERSION ; 
 int G_F_CTLDUMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ctl_req ; 
 int g_debugflags ; 
 int /*<<< orphan*/  g_waitfor_event (int /*<<< orphan*/ ,struct gctl_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gctl_copyin (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_copyout (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_dump (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 int /*<<< orphan*/  imin (int,scalar_t__) ; 
 int /*<<< orphan*/  sbuf_data (int /*<<< orphan*/ ) ; 
 scalar_t__ sbuf_done (int /*<<< orphan*/ ) ; 
 scalar_t__ sbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_new_auto () ; 
 int /*<<< orphan*/  useracc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_ctl_ioctl_ctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag, struct thread *td)
{
	struct gctl_req *req;
	int nerror;

	req = (void *)data;
	req->nerror = 0;
	/* It is an error if we cannot return an error text */
	if (req->lerror < 2)
		return (EINVAL);
	if (!useracc(req->error, req->lerror, VM_PROT_WRITE))
		return (EINVAL);

	req->serror = sbuf_new_auto();
	/* Check the version */
	if (req->version != GCTL_VERSION) {
		gctl_error(req, "kernel and libgeom version mismatch.");
		req->arg = NULL;
	} else {
		/* Get things on board */
		gctl_copyin(req);

		if (g_debugflags & G_F_CTLDUMP)
			gctl_dump(req);

		if (!req->nerror) {
			g_waitfor_event(g_ctl_req, req, M_WAITOK, NULL);
			gctl_copyout(req);
		}
	}
	if (sbuf_done(req->serror)) {
		copyout(sbuf_data(req->serror), req->error,
		    imin(req->lerror, sbuf_len(req->serror) + 1));
	}

	nerror = req->nerror;
	gctl_free(req);
	return (nerror);
}
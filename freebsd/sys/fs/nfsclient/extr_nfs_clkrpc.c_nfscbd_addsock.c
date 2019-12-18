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
struct socket {scalar_t__ so_type; } ;
struct file {struct socket* f_data; int /*<<< orphan*/ * f_ops; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  NFSV4_CBVERS ; 
 int /*<<< orphan*/  NFS_CALLBCKPROG ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SVC_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  badfileops ; 
 int /*<<< orphan*/  nfscb_program ; 
 int /*<<< orphan*/  nfscbd_pool ; 
 int sb_max_adj ; 
 int soreserve (struct socket*,int,int) ; 
 int /*<<< orphan*/ * svc_dg_create (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svc_vc_create (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfscbd_addsock(struct file *fp)
{
	int siz;
	struct socket *so;
	int error;
	SVCXPRT *xprt;

	so = fp->f_data;

	siz = sb_max_adj;
	error = soreserve(so, siz, siz);
	if (error)
		return (error);

	/*
	 * Steal the socket from userland so that it doesn't close
	 * unexpectedly.
	 */
	if (so->so_type == SOCK_DGRAM)
		xprt = svc_dg_create(nfscbd_pool, so, 0, 0);
	else
		xprt = svc_vc_create(nfscbd_pool, so, 0, 0);
	if (xprt) {
		fp->f_ops = &badfileops;
		fp->f_data = NULL;
		svc_reg(xprt, NFS_CALLBCKPROG, NFSV4_CBVERS, nfscb_program,
		    NULL);
		SVC_RELEASE(xprt);
	}

	return (0);
}
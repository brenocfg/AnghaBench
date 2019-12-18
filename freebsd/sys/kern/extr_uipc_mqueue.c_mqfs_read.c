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
struct vop_read_args {struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;
struct uio {int dummy; } ;
struct mqueue {int /*<<< orphan*/  mq_msgsize; int /*<<< orphan*/  mq_curmsgs; int /*<<< orphan*/  mq_maxmsg; int /*<<< orphan*/  mq_totalbytes; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VREG ; 
 struct mqueue* VTOMQ (struct vnode*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int uiomove_frombuf (char*,int,struct uio*) ; 

__attribute__((used)) static int
mqfs_read(struct vop_read_args *ap)
{
	char buf[80];
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	struct mqueue *mq;
	int len, error;

	if (vp->v_type != VREG)
		return (EINVAL);

	mq = VTOMQ(vp);
	snprintf(buf, sizeof(buf),
		"QSIZE:%-10ld MAXMSG:%-10ld CURMSG:%-10ld MSGSIZE:%-10ld\n",
		mq->mq_totalbytes,
		mq->mq_maxmsg,
		mq->mq_curmsgs,
		mq->mq_msgsize);
	buf[sizeof(buf)-1] = '\0';
	len = strlen(buf);
	error = uiomove_frombuf(buf, len, uio);
	return (error);
}
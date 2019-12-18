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
struct uio {scalar_t__ uio_resid; } ;
struct mbuf {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_2__ {int /*<<< orphan*/  hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG ; 
 int EIO ; 
 int ENOBUFS ; 
 scalar_t__ IP_MAXPACKET ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* m_uiotombuf (struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngdwrite(struct cdev *dev, struct uio *uio, int flag)
{
	priv_p	priv = (priv_p )dev->si_drv1;
	struct mbuf *m;
	int error = 0;

	DBG;

	if (uio->uio_resid == 0)
		return (0);

	if (uio->uio_resid < 0 || uio->uio_resid > IP_MAXPACKET)
		return (EIO);

	if ((m = m_uiotombuf(uio, M_NOWAIT, 0, 0, M_PKTHDR)) == NULL)
		return (ENOBUFS);

	NG_SEND_DATA_ONLY(error, priv->hook, m);

	return (error);
}
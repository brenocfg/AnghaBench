#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xuio_t ;
typedef  int /*<<< orphan*/  iovec_t ;
struct TYPE_4__ {int cnt; struct TYPE_4__* bufs; struct TYPE_4__* iovp; } ;
typedef  TYPE_1__ dmu_xuio_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;

/* Variables and functions */
 scalar_t__ UIO_READ ; 
 int /*<<< orphan*/  XUIOSTAT_INCR (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* XUIO_XUZC_PRIV (int /*<<< orphan*/ *) ; 
 scalar_t__ XUIO_XUZC_RW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xuiostat_onloan_rbuf ; 
 int /*<<< orphan*/  xuiostat_onloan_wbuf ; 

void
dmu_xuio_fini(xuio_t *xuio)
{
	dmu_xuio_t *priv = XUIO_XUZC_PRIV(xuio);
	int nblk = priv->cnt;

	kmem_free(priv->iovp, nblk * sizeof (iovec_t));
	kmem_free(priv->bufs, nblk * sizeof (arc_buf_t *));
	kmem_free(priv, sizeof (dmu_xuio_t));

	if (XUIO_XUZC_RW(xuio) == UIO_READ)
		XUIOSTAT_INCR(xuiostat_onloan_rbuf, -nblk);
	else
		XUIOSTAT_INCR(xuiostat_onloan_wbuf, -nblk);
}
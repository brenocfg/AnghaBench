#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/ * tx_br; } ;
typedef  TYPE_1__ qla_tx_fp_t ;
struct TYPE_6__ {struct ifnet* ifp; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mbuf* drbr_dequeue (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla_free_tx_br(qla_host_t *ha, qla_tx_fp_t *fp)
{
        struct mbuf *mp;
        struct ifnet *ifp = ha->ifp;

        if (mtx_initialized(&fp->tx_mtx)) {

                if (fp->tx_br != NULL) {

                        mtx_lock(&fp->tx_mtx);

                        while ((mp = drbr_dequeue(ifp, fp->tx_br)) != NULL) {
                                m_freem(mp);
                        }

                        mtx_unlock(&fp->tx_mtx);

                        buf_ring_free(fp->tx_br, M_DEVBUF);
                        fp->tx_br = NULL;
                }
                mtx_destroy(&fp->tx_mtx);
        }
        return;
}
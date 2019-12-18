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
struct bxe_softc {int num_queues; int unit; struct bxe_fastpath* fp; } ;
struct bxe_fastpath {int /*<<< orphan*/  rx_mtx_name; int /*<<< orphan*/  rx_mtx; int /*<<< orphan*/  tx_mtx_name; int /*<<< orphan*/  tx_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static void
bxe_init_fp_mutexs(struct bxe_softc *sc)
{
    int i;
    struct bxe_fastpath *fp;

    for (i = 0; i < sc->num_queues; i++) {

        fp = &sc->fp[i];

        snprintf(fp->tx_mtx_name, sizeof(fp->tx_mtx_name),
            "bxe%d_fp%d_tx_lock", sc->unit, i);
        mtx_init(&fp->tx_mtx, fp->tx_mtx_name, NULL, MTX_DEF);

        snprintf(fp->rx_mtx_name, sizeof(fp->rx_mtx_name),
            "bxe%d_fp%d_rx_lock", sc->unit, i);
        mtx_init(&fp->rx_mtx, fp->rx_mtx_name, NULL, MTX_DEF);
    }
}
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
struct bxe_softc {int num_queues; struct bxe_fastpath* fp; } ;
struct bxe_fastpath {int /*<<< orphan*/ * tx_br; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_free_buf_rings(struct bxe_softc *sc)
{
#if __FreeBSD_version >= 901504

    int i;
    struct bxe_fastpath *fp;

    for (i = 0; i < sc->num_queues; i++) {

        fp = &sc->fp[i];

        if (fp->tx_br) {
            buf_ring_free(fp->tx_br, M_DEVBUF);
            fp->tx_br = NULL;
        }
    }

#endif
}
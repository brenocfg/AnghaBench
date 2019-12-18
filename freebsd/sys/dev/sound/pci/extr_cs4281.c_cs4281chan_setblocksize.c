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
typedef  int u_int32_t ;
struct sc_info {int bufsz; } ;
struct sc_chinfo {int blksz; scalar_t__ dma_setup; int /*<<< orphan*/  buffer; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int adcdac_go (struct sc_chinfo*,int) ; 
 int /*<<< orphan*/  adcdac_prog (struct sc_chinfo*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
cs4281chan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
    struct sc_chinfo *ch = data;
    struct sc_info *sc = ch->parent;
    u_int32_t go;

    go = adcdac_go(ch, 0);

    /* 2 interrupts are possible and used in buffer (half-empty,empty),
     * hence factor of 2. */
    ch->blksz = MIN(blocksize, sc->bufsz / 2);
    sndbuf_resize(ch->buffer, 2, ch->blksz);
    ch->dma_setup = 0;
    adcdac_prog(ch);
    adcdac_go(ch, go);

    DEB(printf("cs4281chan_setblocksize: blksz %d Setting %d\n", blocksize, ch->blksz));

    return ch->blksz;
}
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
struct snd_dbuf {int flags; int /*<<< orphan*/ * dmamap; int /*<<< orphan*/ * dmatag; scalar_t__ sl; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * shadbuf; int /*<<< orphan*/ * tmpbuf; scalar_t__ buf_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int SNDBUF_F_MANAGED ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
sndbuf_free(struct snd_dbuf *b)
{
	if (b->tmpbuf)
		free(b->tmpbuf, M_DEVBUF);

	if (b->shadbuf)
		free(b->shadbuf, M_DEVBUF);

	if (b->buf) {
		if (b->flags & SNDBUF_F_MANAGED) {
			if (b->buf_addr)
				bus_dmamap_unload(b->dmatag, b->dmamap);
			if (b->dmatag)
				bus_dmamem_free(b->dmatag, b->buf, b->dmamap);
		} else
			free(b->buf, M_DEVBUF);
	}

	b->tmpbuf = NULL;
	b->shadbuf = NULL;
	b->buf = NULL;
	b->sl = 0;
	b->dmatag = NULL;
	b->dmamap = NULL;
}
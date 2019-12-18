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
typedef  int volatile uint32_t ;
struct atiixp_info {int /*<<< orphan*/  dev; } ;
struct atiixp_chinfo {int dt_cur_bit; int blkcnt; int blksz; int volatile ptr; int volatile prevptr; scalar_t__ dir; int /*<<< orphan*/  buffer; struct atiixp_info* parent; } ;

/* Variables and functions */
 int ATI_IXP_DMA_RETRY_MAX ; 
 scalar_t__ PCMDIR_PLAY ; 
 int atiixp_rd (struct atiixp_info*,int volatile) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int volatile,...) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint32_t
atiixp_dmapos(struct atiixp_chinfo *ch)
{
	struct atiixp_info *sc = ch->parent;
	uint32_t reg, addr, sz, retry;
	volatile uint32_t ptr;

	reg = ch->dt_cur_bit;
	addr = sndbuf_getbufaddr(ch->buffer);
	sz = ch->blkcnt * ch->blksz;
	retry = ATI_IXP_DMA_RETRY_MAX;

	do {
		ptr = atiixp_rd(sc, reg);
		if (ptr < addr)
			continue;
		ptr -= addr;
		if (ptr < sz) {
#if 0
#ifdef ATI_IXP_DEBUG
			if ((ptr & ~(ch->blksz - 1)) != ch->ptr) {
				uint32_t delta;

				delta = (sz + ptr - ch->prevptr) % sz;
#ifndef ATI_IXP_DEBUG_VERBOSE
				if (delta < ch->blksz)
#endif
					device_printf(sc->dev,
						"PCMDIR_%s: incoherent DMA "
						"prevptr=%u ptr=%u "
						"ptr=%u blkcnt=%u "
						"[delta=%u != blksz=%u] "
						"(%s)\n",
						(ch->dir == PCMDIR_PLAY) ?
						"PLAY" : "REC",
						ch->prevptr, ptr,
						ch->ptr, ch->blkcnt,
						delta, ch->blksz,
						(delta < ch->blksz) ?
						"OVERLAPPED!" : "Ok");
				ch->ptr = ptr & ~(ch->blksz - 1);
			}
			ch->prevptr = ptr;
#endif
#endif
			return (ptr);
		}
	} while (--retry);

	device_printf(sc->dev, "PCMDIR_%s: invalid DMA pointer ptr=%u\n",
	    (ch->dir == PCMDIR_PLAY) ? "PLAY" : "REC", ptr);

	return (0);
}
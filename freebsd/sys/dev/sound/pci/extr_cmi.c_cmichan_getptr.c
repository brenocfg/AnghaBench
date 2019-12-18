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
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {scalar_t__ dir; int phys_buf; int bps; int /*<<< orphan*/  buffer; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMPCI_REG_DMA0_BASE ; 
 int /*<<< orphan*/  CMPCI_REG_DMA1_BASE ; 
 scalar_t__ PCMDIR_PLAY ; 
 int cmi_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
cmichan_getptr(kobj_t obj, void *data)
{
	struct sc_chinfo	*ch = data;
	struct sc_info		*sc = ch->parent;
	u_int32_t physptr, bufptr, sz;

	snd_mtxlock(sc->lock);
	if (ch->dir == PCMDIR_PLAY) {
		physptr = cmi_rd(sc, CMPCI_REG_DMA0_BASE, 4);
	} else {
		physptr = cmi_rd(sc, CMPCI_REG_DMA1_BASE, 4);
	}
	snd_mtxunlock(sc->lock);

	sz = sndbuf_getsize(ch->buffer);
	bufptr = (physptr - ch->phys_buf + sz - ch->bps) % sz;

	return bufptr;
}
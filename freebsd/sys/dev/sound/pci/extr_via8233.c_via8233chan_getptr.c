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
typedef  int uint32_t ;
struct via_info {scalar_t__ polling; int /*<<< orphan*/  lock; } ;
struct via_chinfo {int ptr; int blksz; int blkcnt; scalar_t__ rbase; struct via_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ VIA_RP_CURRENT_COUNT ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int via_rd (struct via_info*,scalar_t__,int) ; 

__attribute__((used)) static uint32_t
via8233chan_getptr(kobj_t obj, void *data)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;
	uint32_t v, index, count, ptr;

	snd_mtxlock(via->lock);
	if (via->polling != 0) {
		ptr = ch->ptr;
		snd_mtxunlock(via->lock);
	} else {
		v = via_rd(via, ch->rbase + VIA_RP_CURRENT_COUNT, 4);
		snd_mtxunlock(via->lock);
		index = v >> 24;		/* Last completed buffer */
		count = v & 0x00ffffff;	/* Bytes remaining */
		ptr = (index + 1) * ch->blksz - count;
		ptr %= ch->blkcnt * ch->blksz;	/* Wrap to available space */
	}

	return (ptr);
}
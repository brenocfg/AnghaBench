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
struct via_info {int dummy; } ;
struct via_chinfo {scalar_t__ active; int blksz; int blkcnt; int ptr; int prevptr; scalar_t__ rbase; struct via_info* parent; int /*<<< orphan*/ * channel; } ;

/* Variables and functions */
 scalar_t__ VIA_RP_CURRENT_COUNT ; 
 int via_rd (struct via_info*,scalar_t__,int) ; 

__attribute__((used)) static __inline int
via_poll_channel(struct via_chinfo *ch)
{
	struct via_info *via;
	uint32_t sz, delta;
	uint32_t v, index, count;
	int ptr;

	if (ch == NULL || ch->channel == NULL || ch->active == 0)
		return (0);

	via = ch->parent;
	sz = ch->blksz * ch->blkcnt;
	v = via_rd(via, ch->rbase + VIA_RP_CURRENT_COUNT, 4);
	index = v >> 24;
	count = v & 0x00ffffff;
	ptr = ((index + 1) * ch->blksz) - count;
	ptr %= sz;
	ptr &= ~(ch->blksz - 1);
	ch->ptr = ptr;
	delta = (sz + ptr - ch->prevptr) % sz;

	if (delta < ch->blksz)
		return (0);

	ch->prevptr = ptr;

	return (1);
}
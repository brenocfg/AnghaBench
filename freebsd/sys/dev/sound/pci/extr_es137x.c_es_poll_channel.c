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
struct es_info {int dummy; } ;
struct es_chinfo {scalar_t__ active; scalar_t__ dir; scalar_t__ index; int blksz; int blkcnt; int ptr; int prevptr; struct es_info* parent; int /*<<< orphan*/ * channel; } ;

/* Variables and functions */
 int ES1370_REG_ADC_FRAMECNT ; 
 int ES1370_REG_DAC1_FRAMECNT ; 
 int ES1370_REG_DAC2_FRAMECNT ; 
 int /*<<< orphan*/  ES1370_REG_MEMPAGE ; 
 scalar_t__ ES_DAC1 ; 
 scalar_t__ PCMDIR_PLAY ; 
 int es_rd (struct es_info*,int,int) ; 
 int /*<<< orphan*/  es_wr (struct es_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __inline int
es_poll_channel(struct es_chinfo *ch)
{
	struct es_info *es;
	uint32_t sz, delta;
	uint32_t reg, ptr;

	if (ch == NULL || ch->channel == NULL || ch->active == 0)
		return (0);

	es = ch->parent;
	if (ch->dir == PCMDIR_PLAY) {
		if (ch->index == ES_DAC1)
			reg = ES1370_REG_DAC1_FRAMECNT;
		else
			reg = ES1370_REG_DAC2_FRAMECNT;
	} else
		reg = ES1370_REG_ADC_FRAMECNT;
	sz = ch->blksz * ch->blkcnt;
	es_wr(es, ES1370_REG_MEMPAGE, reg >> 8, 4);
	ptr = es_rd(es, reg & 0x000000ff, 4) >> 16;
	ptr <<= 2;
	ch->ptr = ptr;
	ptr %= sz;
	ptr &= ~(ch->blksz - 1);
	delta = (sz + ptr - ch->prevptr) % sz;

	if (delta < ch->blksz)
		return (0);

	ch->prevptr = ptr;

	return (1);
}
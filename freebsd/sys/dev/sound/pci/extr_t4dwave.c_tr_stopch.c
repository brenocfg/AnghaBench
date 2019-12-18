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
struct tr_info {int dummy; } ;
struct tr_chinfo {int index; struct tr_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  TR_REG_STOPA ; 
 int /*<<< orphan*/  TR_REG_STOPB ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
tr_stopch(struct tr_chinfo *ch)
{
	struct tr_info *tr = ch->parent;
	int bank, chan;

	bank = (ch->index & 0x20) ? 1 : 0;
	chan = ch->index & 0x1f;
	tr_wr(tr, bank? TR_REG_STOPB : TR_REG_STOPA, 1 << chan, 4);
}
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
 int TR_CIR_MASK ; 
 int /*<<< orphan*/  TR_REG_CIR ; 
 int tr_rd (struct tr_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
tr_selch(struct tr_chinfo *ch)
{
	struct tr_info *tr = ch->parent;
	int i;

	i = tr_rd(tr, TR_REG_CIR, 4);
	i &= ~TR_CIR_MASK;
	i |= ch->index & 0x3f;
	tr_wr(tr, TR_REG_CIR, i, 4);
}
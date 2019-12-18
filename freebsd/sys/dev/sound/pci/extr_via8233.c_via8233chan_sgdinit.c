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
struct via_info {scalar_t__ sgd_addr; int /*<<< orphan*/ * sgd_table; } ;
struct via_dma_op {int dummy; } ;
struct via_chinfo {scalar_t__ sgd_addr; int /*<<< orphan*/ * sgd_table; } ;

/* Variables and functions */
 int VIA_SEGS_MAX ; 

__attribute__((used)) static void
via8233chan_sgdinit(struct via_info *via, struct via_chinfo *ch, int chnum)
{
	ch->sgd_table = &via->sgd_table[chnum * VIA_SEGS_MAX];
	ch->sgd_addr = via->sgd_addr + chnum * VIA_SEGS_MAX *
	    sizeof(struct via_dma_op);
}
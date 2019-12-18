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
struct ttyinq_block {int /*<<< orphan*/  tib_data; struct ttyinq_block* tib_next; } ;
struct ttyinq {struct ttyinq_block* ti_firstblock; scalar_t__ ti_end; scalar_t__ ti_reprint; scalar_t__ ti_linestart; scalar_t__ ti_begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ttyinq_flush_secure ; 

void
ttyinq_flush(struct ttyinq *ti)
{
	struct ttyinq_block *tib;

	ti->ti_begin = 0;
	ti->ti_linestart = 0;
	ti->ti_reprint = 0;
	ti->ti_end = 0;

	/* Zero all data in the input queue to get rid of passwords. */
	if (ttyinq_flush_secure) {
		for (tib = ti->ti_firstblock; tib != NULL; tib = tib->tib_next)
			bzero(&tib->tib_data, sizeof tib->tib_data);
	}
}
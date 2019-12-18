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
struct ttyinq_block {int dummy; } ;
struct ttyinq {scalar_t__ ti_nblocks; struct ttyinq_block* ti_firstblock; scalar_t__ ti_quota; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TTYINQ_REMOVE_HEAD (struct ttyinq*) ; 
 int /*<<< orphan*/  ttyinq_flush (struct ttyinq*) ; 
 int /*<<< orphan*/  ttyinq_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct ttyinq_block*) ; 

void
ttyinq_free(struct ttyinq *ti)
{
	struct ttyinq_block *tib;

	ttyinq_flush(ti);
	ti->ti_quota = 0;

	while ((tib = ti->ti_firstblock) != NULL) {
		TTYINQ_REMOVE_HEAD(ti);
		uma_zfree(ttyinq_zone, tib);
	}

	MPASS(ti->ti_nblocks == 0);
}
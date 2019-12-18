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
struct ttyoutq_block {int dummy; } ;
struct ttyoutq {scalar_t__ to_nblocks; struct ttyoutq_block* to_firstblock; scalar_t__ to_quota; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TTYOUTQ_REMOVE_HEAD (struct ttyoutq*) ; 
 int /*<<< orphan*/  ttyoutq_flush (struct ttyoutq*) ; 
 int /*<<< orphan*/  ttyoutq_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct ttyoutq_block*) ; 

void
ttyoutq_free(struct ttyoutq *to)
{
	struct ttyoutq_block *tob;

	ttyoutq_flush(to);
	to->to_quota = 0;

	while ((tob = to->to_firstblock) != NULL) {
		TTYOUTQ_REMOVE_HEAD(to);
		uma_zfree(ttyoutq_zone, tob);
	}

	MPASS(to->to_nblocks == 0);
}
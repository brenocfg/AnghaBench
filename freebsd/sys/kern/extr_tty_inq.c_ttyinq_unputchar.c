#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttyinq {int ti_linestart; int ti_end; TYPE_1__* ti_lastblock; } ;
struct TYPE_2__ {struct TYPE_2__* tib_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int TTYINQ_DATASIZE ; 

void
ttyinq_unputchar(struct ttyinq *ti)
{

	MPASS(ti->ti_linestart < ti->ti_end);

	if (--ti->ti_end % TTYINQ_DATASIZE == 0) {
		/* Roll back to the previous block. */
		ti->ti_lastblock = ti->ti_lastblock->tib_prev;
		/*
		 * This can only fail if we are unputchar()'ing the
		 * first character in the queue.
		 */
		MPASS((ti->ti_lastblock == NULL) == (ti->ti_end == 0));
	}
}
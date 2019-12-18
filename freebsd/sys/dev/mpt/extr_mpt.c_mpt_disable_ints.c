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
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 int MPT_INTR_DB_MASK ; 
 int MPT_INTR_REPLY_MASK ; 
 int /*<<< orphan*/  MPT_OFFSET_INTR_MASK ; 
 int /*<<< orphan*/  mpt_write (struct mpt_softc*,int /*<<< orphan*/ ,int) ; 

void
mpt_disable_ints(struct mpt_softc *mpt)
{

	/* Mask all interrupts */
	mpt_write(mpt, MPT_OFFSET_INTR_MASK,
	    MPT_INTR_REPLY_MASK | MPT_INTR_DB_MASK);
}
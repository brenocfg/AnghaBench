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
 int /*<<< orphan*/  MPT_INTR_DB_MASK ; 
 int /*<<< orphan*/  MPT_OFFSET_INTR_MASK ; 
 int /*<<< orphan*/  mpt_write (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mpt_enable_ints(struct mpt_softc *mpt)
{

	/* Unmask every thing except door bell int */
	mpt_write(mpt, MPT_OFFSET_INTR_MASK, MPT_INTR_DB_MASK);
}
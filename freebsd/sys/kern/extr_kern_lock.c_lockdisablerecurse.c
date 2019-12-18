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
struct TYPE_2__ {int /*<<< orphan*/  lo_flags; } ;
struct lock {TYPE_1__ lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KA_XLOCKED ; 
 int /*<<< orphan*/  LO_RECURSABLE ; 
 int /*<<< orphan*/  lockmgr_assert (struct lock*,int /*<<< orphan*/ ) ; 

void
lockdisablerecurse(struct lock *lk)
{

	lockmgr_assert(lk, KA_XLOCKED);
	lk->lock_object.lo_flags &= ~LO_RECURSABLE;
}
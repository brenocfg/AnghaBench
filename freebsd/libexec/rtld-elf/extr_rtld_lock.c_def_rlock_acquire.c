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
struct TYPE_2__ {int lock; } ;
typedef  TYPE_1__ Lock ;

/* Variables and functions */
 int /*<<< orphan*/  RC_INCR ; 
 int WAFLAG ; 
 int /*<<< orphan*/  atomic_add_acq_int (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
def_rlock_acquire(void *lock)
{
    Lock *l = (Lock *)lock;

    atomic_add_acq_int(&l->lock, RC_INCR);
    while (l->lock & WAFLAG)
	    ;	/* Spin */
}
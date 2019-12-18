#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ value; } ;
typedef  TYPE_1__ cvmx_spinlock_rec_t ;

/* Variables and functions */
 scalar_t__ CVMX_SPINLOCK_UNLOCKED_VAL ; 

__attribute__((used)) static inline int cvmx_spinlock_rec_locked(cvmx_spinlock_rec_t *lock)
{
    return (lock->value != CVMX_SPINLOCK_UNLOCKED_VAL);
}
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
typedef  unsigned long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNCWS ; 

__attribute__((used)) static inline void cvmx_spinlock_bit_unlock(uint32_t *word)
{
    CVMX_SYNCWS;
    *word &= ~(1UL << 31) ;
    CVMX_SYNCWS;
}
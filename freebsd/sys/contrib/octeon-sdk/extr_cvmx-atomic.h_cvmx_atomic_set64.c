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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNCWS ; 

__attribute__((used)) static inline void cvmx_atomic_set64(int64_t *ptr, int64_t value)
{
    CVMX_SYNCWS;
    *ptr = value;
    CVMX_SYNCWS;
}
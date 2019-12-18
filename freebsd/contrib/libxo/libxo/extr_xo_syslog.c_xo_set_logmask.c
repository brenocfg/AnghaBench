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

/* Variables and functions */
 int /*<<< orphan*/  THREAD_LOCK () ; 
 int /*<<< orphan*/  THREAD_UNLOCK () ; 
 int xo_logmask ; 

int
xo_set_logmask (int pmask)
{
    int omask;

    THREAD_LOCK();
    omask = xo_logmask;
    if (pmask != 0)
        xo_logmask = pmask;
    THREAD_UNLOCK();
    return (omask);
}
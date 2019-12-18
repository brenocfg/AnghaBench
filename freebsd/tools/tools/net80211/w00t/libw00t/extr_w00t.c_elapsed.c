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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int elapsed(struct timeval *past, struct timeval *now)
{       
        int el;
        
        el = now->tv_sec - past->tv_sec;
        assert(el >= 0);
        if (el == 0) {
                el = now->tv_usec - past->tv_usec;
        } else {
                el = (el - 1)*1000*1000;
                el += 1000*1000-past->tv_usec;
                el += now->tv_usec;
        }
        
        return el;
}
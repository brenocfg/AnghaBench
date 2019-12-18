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
typedef  int time_t ;
typedef  int UINT16 ;

/* Variables and functions */
 int CLOCKS_PER_SEC ; 
 int clock () ; 

time_t time(time_t *t)
{
    UINT16 ret;

    /* Should be relative to 0:00 1970 GMT but hey */
    ret = clock() / CLOCKS_PER_SEC;

    if (t)
	*t = ret;

    return ret;
}
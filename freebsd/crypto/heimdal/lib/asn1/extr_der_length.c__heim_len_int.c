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

size_t
_heim_len_int (int val)
{
    unsigned char q;
    size_t ret = 0;

    if (val >= 0) {
	do {
	    q = val % 256;
	    ret++;
	    val /= 256;
	} while(val);
	if(q >= 128)
	    ret++;
    } else {
	val = ~val;
	do {
	    q = ~(val % 256);
	    ret++;
	    val /= 256;
	} while(val);
	if(q < 128)
	    ret++;
    }
    return ret;
}
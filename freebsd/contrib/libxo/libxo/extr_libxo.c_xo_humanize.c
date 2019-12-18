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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HN_DIVISOR_1000 ; 
 int /*<<< orphan*/  xo_humanize_number (char*,int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static ssize_t
xo_humanize (char *buf, ssize_t len, uint64_t value, int flags)
{
    int scale = 0;

    if (value) {
	uint64_t left = value;

	if (flags & HN_DIVISOR_1000) {
	    for ( ; left; scale++)
		left /= 1000;
	} else {
	    for ( ; left; scale++)
		left /= 1024;
	}
	scale -= 1;
    }
    
    return xo_humanize_number(buf, len, value, "", scale, flags);
}
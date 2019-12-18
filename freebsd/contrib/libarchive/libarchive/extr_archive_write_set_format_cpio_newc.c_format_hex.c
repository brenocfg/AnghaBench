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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  format_hex_recursive (int,char*,int) ; 

__attribute__((used)) static int
format_hex(int64_t v, void *p, int digits)
{
	int64_t	max;
	int	ret;

	max = (((int64_t)1) << (digits * 4)) - 1;
	if (v >= 0  &&  v <= max) {
	    format_hex_recursive(v, (char *)p, digits);
	    ret = 0;
	} else {
	    format_hex_recursive(max, (char *)p, digits);
	    ret = -1;
	}
	return (ret);
}
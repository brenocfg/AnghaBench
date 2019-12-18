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
 scalar_t__ getsubopt (char**,char* const*,char**) ; 

int
main(void)
{
	char buf[] = "k=v";
	char *options = buf;
	char token0[] = "k";
	char *const tokens[] = { token0, NULL };
	char *value = NULL;
	return ! (getsubopt(&options, tokens, &value) == 0
	    && value == buf+2 && options == buf+3);
}
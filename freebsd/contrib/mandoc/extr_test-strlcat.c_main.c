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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int strlcat (char*,char*,int) ; 

int
main(void)
{
	char buf[3] = "a";
	return ! (strlcat(buf, "b", sizeof(buf)) == 2 &&
	    buf[0] == 'a' && buf[1] == 'b' && buf[2] == '\0');
}
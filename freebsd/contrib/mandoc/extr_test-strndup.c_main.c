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
 char* strndup (char*,int) ; 

int
main(void)
{
	char *s;

	s = strndup("123", 2);
	return s[0] != '1' ? 1 : s[1] != '2' ? 2 : s[2] != '\0' ? 3 : 0;
}
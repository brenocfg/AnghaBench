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
typedef  size_t u_int ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
simple_hex(void *ptr, size_t length, const char *separator)
{
	unsigned char *cp;
	u_int i;

	if (length == 0)
		return;
	cp = ptr;
	printf("%02x", cp[0]);
	for (i = 1; i < length; i++)
		printf("%s%02x", separator, cp[i]);
}
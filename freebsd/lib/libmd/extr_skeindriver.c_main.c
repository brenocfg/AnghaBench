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
 int SKEIN ; 
 int /*<<< orphan*/  SKEINString (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
main(void)
{
	printf("SKEIN%d test suite:\n", SKEIN);

	SKEINString("");
	SKEINString("abc");
	SKEINString("message digest");
	SKEINString("abcdefghijklmnopqrstuvwxyz");
	SKEINString("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		  "abcdefghijklmnopqrstuvwxyz0123456789");
	SKEINString("1234567890123456789012345678901234567890"
		  "1234567890123456789012345678901234567890");

	return 0;
}
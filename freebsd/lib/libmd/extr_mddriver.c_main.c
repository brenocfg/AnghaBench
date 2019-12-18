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
 int MD ; 
 int /*<<< orphan*/  MDString (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
main(void)
{
	printf("MD%d test suite:\n", MD);

	MDString("");
	MDString("a");
	MDString("abc");
	MDString("message digest");
	MDString("abcdefghijklmnopqrstuvwxyz");
	MDString("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789");
	MDString("1234567890123456789012345678901234567890"
		"1234567890123456789012345678901234567890");

	return 0;
}
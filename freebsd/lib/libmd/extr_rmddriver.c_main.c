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
 int /*<<< orphan*/  RIPEMD160String (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
main(void)
{
	printf("RIPEMD160 test suite:\n");

	RIPEMD160String("");
	RIPEMD160String("abc");
	RIPEMD160String("message digest");
	RIPEMD160String("abcdefghijklmnopqrstuvwxyz");
	RIPEMD160String("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789");
	RIPEMD160String("1234567890123456789012345678901234567890"
		"1234567890123456789012345678901234567890");

	return 0;
}
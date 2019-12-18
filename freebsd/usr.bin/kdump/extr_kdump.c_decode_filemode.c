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
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysdecode_filemode (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void
decode_filemode(int value)
{
	bool invalid;
	int rem;

	if (value == 0) {
		printf("0");
		return;
	}
	printf("%#o<", value);
	invalid = !sysdecode_filemode(stdout, value, &rem);
	printf(">");
	if (invalid)
		printf("<invalid>%u", rem);
}
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
 int /*<<< orphan*/  FE_INVALID ; 
 int /*<<< orphan*/  feenableexcept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  testnan (char*) ; 

int
main(void)
{

	printf("1..1\n");

	/* Die if a signalling NaN is returned */
	feenableexcept(FE_INVALID);

	testnan("0x1234");
	testnan("");

	printf("ok 1 - nan\n");

	return (0);
}
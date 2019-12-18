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
 int /*<<< orphan*/  printf (char*,int) ; 
 float pythagorean_theorem (int,int) ; 

int
main(int argc, char *argv[])
{
	float hypotenuse = pythagorean_theorem(3, 4);
	printf("the hypotenuse of 3 and 4 is %d\n", (int) hypotenuse);

	return 0;
}
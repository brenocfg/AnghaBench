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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  portdev_t ;

/* Variables and functions */
 char* iMajorError ; 
 char* iMinorError ; 
 scalar_t__ major_12_12_8 (int /*<<< orphan*/ ) ; 
 scalar_t__ major_12_20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makedev_12_12_8 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  makedev_12_20 (scalar_t__,scalar_t__) ; 
 scalar_t__ minor_12_20 (int /*<<< orphan*/ ) ; 
 scalar_t__ subunit_12_12_8 (int /*<<< orphan*/ ) ; 
 char* tooManyFields ; 
 scalar_t__ unit_12_12_8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static portdev_t
pack_bsdos(int n, u_long numbers[], const char **error)
{
	portdev_t dev = 0;

	if (n == 2) {
		dev = makedev_12_20(numbers[0], numbers[1]);
		if ((u_long)major_12_20(dev) != numbers[0])
			*error = iMajorError;
		if ((u_long)minor_12_20(dev) != numbers[1])
			*error = iMinorError;
	} else if (n == 3) {
		dev = makedev_12_12_8(numbers[0], numbers[1], numbers[2]);
		if ((u_long)major_12_12_8(dev) != numbers[0])
			*error = iMajorError;
		if ((u_long)unit_12_12_8(dev) != numbers[1])
			*error = "invalid unit number";
		if ((u_long)subunit_12_12_8(dev) != numbers[2])
			*error = "invalid subunit number";
	} else
		*error = tooManyFields;
	return (dev);
}
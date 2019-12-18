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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  apd_makedev (unsigned long,unsigned long) ; 
 char* iMajorError ; 
 char* iMinorError ; 
 scalar_t__ major (int /*<<< orphan*/ ) ; 
 scalar_t__ minor (int /*<<< orphan*/ ) ; 
 char* tooManyFields ; 

dev_t
pack_native(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = apd_makedev(numbers[0], numbers[1]);
		if ((unsigned long)major(dev) != numbers[0])
			*error = iMajorError;
		else if ((unsigned long)minor(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}
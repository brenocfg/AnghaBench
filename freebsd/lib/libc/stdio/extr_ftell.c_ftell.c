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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ LONG_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 

long
ftell(FILE *fp)
{
	off_t rv;

	rv = ftello(fp);
	if (rv > LONG_MAX) {
		errno = EOVERFLOW;
		return (-1);
	}
	return (rv);
}
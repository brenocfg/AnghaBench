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
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comc_parseint(const char *speedstr)
{
	char *p;
	int speed;

	speed = strtol(speedstr, &p, 0);
	if (p == speedstr || *p != '\0' || speed <= 0)
		return (-1);

	return (speed);
}
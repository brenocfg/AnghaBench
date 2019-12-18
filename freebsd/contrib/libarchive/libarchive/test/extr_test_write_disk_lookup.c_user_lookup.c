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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int64_t
user_lookup(void *d, const char *name, int64_t u)
{
	int *mp = d;

	(void)u; /* UNUSED */

	assertEqualInt(*mp, 0x1234);
	if (strcmp("FOO", name) == 0)
		return (2);
	return (74);
}
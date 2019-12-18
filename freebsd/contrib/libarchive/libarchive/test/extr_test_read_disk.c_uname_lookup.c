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

__attribute__((used)) static const char *
uname_lookup(void *d, int64_t u)
{
	int *mp = d;
	assertEqualInt(*mp, 0x1234);
	if (u == 1)
		return ("FOO");
	return ("NOTFOO");
}
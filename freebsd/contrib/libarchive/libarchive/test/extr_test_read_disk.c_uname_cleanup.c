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
 int /*<<< orphan*/  assertEqualInt (int,int) ; 

__attribute__((used)) static void
uname_cleanup(void *d)
{
	int *mp = d;
	assertEqualInt(*mp, 0x1234);
	*mp = 0x2345;
}
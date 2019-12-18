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
 int /*<<< orphan*/  NOPID ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int findslot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
findfreeslot(void)
{
	int slot;

	if ((slot = findslot(NOPID)) < 0)
		errx(1, "internal error: no free pid slot");
	return (slot);
}
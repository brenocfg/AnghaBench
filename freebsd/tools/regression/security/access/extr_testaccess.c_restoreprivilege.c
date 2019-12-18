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
 int /*<<< orphan*/  ROOT_UID ; 
 int /*<<< orphan*/  WHEEL_GID ; 
 int setregid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setreuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
restoreprivilege(void)
{
	int error;

	error = setreuid(ROOT_UID, ROOT_UID);
	if (error)
		return (error);

	error = setregid(WHEEL_GID, WHEEL_GID);
	if (error)
		return (error);

	return (0);
}
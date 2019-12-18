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
 int /*<<< orphan*/ * envVars ; 
 int envVarsTotal ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
__remove_putenv(int envNdx)
{
	envVarsTotal--;
	if (envVarsTotal > envNdx)
		memmove(&(envVars[envNdx]), &(envVars[envNdx + 1]),
		    (envVarsTotal - envNdx) * sizeof (*envVars));
	memset(&(envVars[envVarsTotal]), 0, sizeof (*envVars));

	return;
}
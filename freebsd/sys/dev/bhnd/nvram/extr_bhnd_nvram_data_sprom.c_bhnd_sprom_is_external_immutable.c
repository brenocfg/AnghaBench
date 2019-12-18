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
 int /*<<< orphan*/  BHND_NVAR_SROMREV ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bhnd_sprom_is_external_immutable(const char *name)
{
	/* The layout revision is immutable and cannot be changed */
	if (strcmp(name, BHND_NVAR_SROMREV) == 0)
		return (true);

	return (false);
}
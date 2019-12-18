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
typedef  enum roff_sec { ____Placeholder_roff_sec } roff_sec ;

/* Variables and functions */
 int SEC_CUSTOM ; 
 scalar_t__ SEC__MAX ; 
 scalar_t__* secnames ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

enum roff_sec
mdoc_a2sec(const char *p)
{
	int		 i;

	for (i = 0; i < (int)SEC__MAX; i++)
		if (secnames[i] && 0 == strcmp(p, secnames[i]))
			return (enum roff_sec)i;

	return SEC_CUSTOM;
}
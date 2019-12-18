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
 scalar_t__ KSTAT_STRLEN ; 
 int /*<<< orphan*/  bzero (char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,scalar_t__) ; 

void
kstat_set_string(char *dst, const char *src)
{

	bzero(dst, KSTAT_STRLEN);
	(void) strncpy(dst, src, KSTAT_STRLEN - 1);
}
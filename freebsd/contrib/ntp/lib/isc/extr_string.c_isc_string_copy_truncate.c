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
 int /*<<< orphan*/  ENSURE (int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char*) ; 

void
isc_string_copy_truncate(char *target, size_t size, const char *source) {
	REQUIRE(size > 0U);

	strlcpy(target, source, size);

	ENSURE(strlen(target) < size);
}
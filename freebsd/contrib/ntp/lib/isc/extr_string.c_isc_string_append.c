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
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int) ; 
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_STRING_MAGIC ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlcat (char*,char const*,size_t) ; 
 size_t strlen (char*) ; 

isc_result_t
isc_string_append(char *target, size_t size, const char *source) {
	REQUIRE(size > 0U);
	REQUIRE(strlen(target) < size);

	if (strlcat(target, source, size) >= size) {
		memset(target, ISC_STRING_MAGIC, size);
		return (ISC_R_NOSPACE);
	}

	ENSURE(strlen(target) < size);

	return (ISC_R_SUCCESS);
}
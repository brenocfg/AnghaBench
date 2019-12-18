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
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (char const) ; 

isc_boolean_t
isc_file_isabsolute(const char *filename) {
	REQUIRE(filename != NULL);
	/*
	 * Look for c:\path\... style, c:/path/... or \\computer\shar\path...
	 * the UNC style file specs
	 */
	if ((filename[0] == '\\') && (filename[1] == '\\'))
		return (ISC_TRUE);
	if (isalpha(filename[0]) && filename[1] == ':' && filename[2] == '\\')
		return (ISC_TRUE);
	if (isalpha(filename[0]) && filename[1] == ':' && filename[2] == '/')
		return (ISC_TRUE);
	return (ISC_FALSE);
}
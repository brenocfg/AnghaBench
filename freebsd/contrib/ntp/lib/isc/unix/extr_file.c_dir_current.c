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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ errno ; 
 char* getcwd (char*,size_t) ; 
 int /*<<< orphan*/  isc__errno2result (scalar_t__) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static isc_result_t
dir_current(char *dirname, size_t length) {
	char *cwd;
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(dirname != NULL);
	REQUIRE(length > 0U);

	cwd = getcwd(dirname, length);

	if (cwd == NULL) {
		if (errno == ERANGE)
			result = ISC_R_NOSPACE;
		else
			result = isc__errno2result(errno);
	} else {
		if (strlen(dirname) + 1 == length)
			result = ISC_R_NOSPACE;
		else if (dirname[1] != '\0')
			strlcat(dirname, "/", length);
	}

	return (result);
}
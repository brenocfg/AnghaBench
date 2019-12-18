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
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

isc_result_t
isc_file_template(const char *path, const char *templet, char *buf,
			size_t buflen) {
	char *s;

	REQUIRE(path != NULL);
	REQUIRE(templet != NULL);
	REQUIRE(buf != NULL);

	s = strrchr(templet, '\\');
	if (s != NULL)
		templet = s + 1;

	s = strrchr(path, '\\');

	if (s != NULL) {
		if ((s - path + 1 + strlen(templet) + 1) > buflen)
			return (ISC_R_NOSPACE);

		strncpy(buf, path, s - path + 1);
		buf[s - path + 1] = '\0';
		strcat(buf, templet);
	} else {
		if ((strlen(templet) + 1) > buflen)
			return (ISC_R_NOSPACE);

		strcpy(buf, templet);
	}

	return (ISC_R_SUCCESS);
}
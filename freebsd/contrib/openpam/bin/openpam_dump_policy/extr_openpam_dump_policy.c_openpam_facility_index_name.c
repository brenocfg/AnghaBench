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
typedef  size_t pam_facility_t ;

/* Variables and functions */
 int asprintf (char**,char*,char const*) ; 
 char** pam_facility_name ; 
 char toupper (unsigned char) ; 

__attribute__((used)) static char *
openpam_facility_index_name(pam_facility_t fclt)
{
	const char *facility = pam_facility_name[fclt];
	char *name, *p;

	if (asprintf(&name, "PAM_%s", facility) == -1)
		return (NULL);
	for (p = name + 4; *p; ++p)
		*p = toupper((unsigned char)*p);
	return (name);
}
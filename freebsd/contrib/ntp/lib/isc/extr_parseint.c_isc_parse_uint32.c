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
typedef  unsigned long isc_uint32_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  ISC_R_BADNUMBER ; 
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 unsigned long strtoul (char const*,char**,int) ; 

isc_result_t
isc_parse_uint32(isc_uint32_t *uip, const char *string, int base) {
	unsigned long n;
	char *e;
	if (! isalnum((unsigned char)(string[0])))
		return (ISC_R_BADNUMBER);
	errno = 0;
	n = strtoul(string, &e, base);
	if (*e != '\0')
		return (ISC_R_BADNUMBER);
	if (n == ULONG_MAX && errno == ERANGE)
		return (ISC_R_RANGE);
	*uip = n;
	return (ISC_R_SUCCESS);
}
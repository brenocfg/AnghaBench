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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_INVALID_STR ; 
 int /*<<< orphan*/  ldns_str2rdf_hex (int /*<<< orphan*/ **,char const*) ; 
 size_t strlen (char const*) ; 

ldns_status
ldns_str2rdf_nsap(ldns_rdf **rd, const char *str)
{
    size_t len, i;
    char* nsap_str = (char*) str;

	/* just a hex string with optional dots? */
	if (str[0] != '0' || str[1] != 'x') {
		return LDNS_STATUS_INVALID_STR;
	} else {
		len = strlen(str);
		for (i=0; i < len; i++) {
			if (nsap_str[i] == '.')
				nsap_str[i] = ' ';
        }
		return ldns_str2rdf_hex(rd, str+2);
	}
}
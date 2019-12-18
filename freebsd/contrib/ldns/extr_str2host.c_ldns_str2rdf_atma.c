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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_str2rdf_hex (int /*<<< orphan*/ **,char const*) ; 
 size_t strlen (char const*) ; 

ldns_status
ldns_str2rdf_atma(ldns_rdf **rd, const char *str)
{
    size_t len, i;
    char* atma_str = (char*) str;
	ldns_status status;

	/* just a hex string with optional dots? */
	len = strlen(str);
	for (i=0; i < len; i++) {
		if (atma_str[i] == '.')
			atma_str[i] = ' ';
	}
	status = ldns_str2rdf_hex(rd, str);
    if (status != LDNS_STATUS_OK) {
		; /* probably in e.164 format than */
	}
	return status;
}
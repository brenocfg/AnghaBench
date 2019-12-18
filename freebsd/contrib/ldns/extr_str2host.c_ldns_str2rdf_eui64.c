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
typedef  unsigned int uint8_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_EUI64 ; 
 int /*<<< orphan*/  LDNS_STATUS_INVALID_EUI64 ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,int,unsigned int**) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int*) ; 
 scalar_t__ strlen (char const*) ; 

ldns_status
ldns_str2rdf_eui64(ldns_rdf **rd, const char *str)
{
	unsigned int a, b, c, d, e, f, g, h;
	uint8_t bytes[8];
	int l;

	if (sscanf(str, "%2x-%2x-%2x-%2x-%2x-%2x-%2x-%2x%n",
			&a, &b, &c, &d, &e, &f, &g, &h, &l) != 8 ||
			l != (int)strlen(str)) {
		return LDNS_STATUS_INVALID_EUI64;
	} else {
		bytes[0] = a;
		bytes[1] = b;
		bytes[2] = c;
		bytes[3] = d;
		bytes[4] = e;
		bytes[5] = f;
		bytes[6] = g;
		bytes[7] = h;
		*rd = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_EUI64, 8, &bytes);
	}
	return *rd ? LDNS_STATUS_OK : LDNS_STATUS_MEM_ERR;
}
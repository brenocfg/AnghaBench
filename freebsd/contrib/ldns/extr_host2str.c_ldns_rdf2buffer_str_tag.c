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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_WIRE_RDATA_ERR ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 size_t* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_rdf2buffer_str_tag(ldns_buffer *output, const ldns_rdf *rdf)
{
	size_t nchars;
	const uint8_t* chars;
	char ch;
	if (ldns_rdf_size(rdf) < 2) {
		return LDNS_STATUS_WIRE_RDATA_ERR;
	}
	nchars = ldns_rdf_data(rdf)[0];
	if (nchars >= ldns_rdf_size(rdf) || /* should be rdf_size - 1 */
			nchars < 1) {
		return LDNS_STATUS_WIRE_RDATA_ERR;
	}
	chars = ldns_rdf_data(rdf) + 1;
	while (nchars > 0) {
		ch = (char)*chars++;
		if (! isalnum((unsigned char)ch)) {
			return LDNS_STATUS_WIRE_RDATA_ERR;
		}
		ldns_buffer_printf(output, "%c", ch);
		nchars--;
	}
	return ldns_buffer_status(output);
}
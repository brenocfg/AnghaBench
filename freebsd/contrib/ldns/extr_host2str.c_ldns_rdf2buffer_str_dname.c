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
 size_t LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_STATUS_DOMAINNAME_OVERFLOW ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isgraph (unsigned char) ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_rdf2buffer_str_dname(ldns_buffer *output, const ldns_rdf *dname)
{
	/* can we do with 1 pos var? or without at all? */
	uint8_t src_pos = 0;
	uint8_t len;
	uint8_t *data;
	uint8_t i;
	unsigned char c;

	data = (uint8_t*)ldns_rdf_data(dname);
	len = data[src_pos];

	if (ldns_rdf_size(dname) > LDNS_MAX_DOMAINLEN) {
		/* too large, return */
		return LDNS_STATUS_DOMAINNAME_OVERFLOW;
	}

	/* special case: root label */
	if (1 == ldns_rdf_size(dname)) {
		ldns_buffer_printf(output, ".");
	} else {
		while ((len > 0) && src_pos < ldns_rdf_size(dname)) {
			src_pos++;
			for(i = 0; i < len; i++) {
				/* paranoia check for various 'strange'
				   characters in dnames
				*/
				c = (unsigned char) data[src_pos];
				if(c == '.' || c == ';' ||
				   c == '(' || c == ')' ||
				   c == '\\') {
					ldns_buffer_printf(output, "\\%c",
							data[src_pos]);
				} else if (!(isascii(c) && isgraph(c))) {
					ldns_buffer_printf(output, "\\%03u",
						        data[src_pos]);
				} else {
					ldns_buffer_printf(output, "%c", data[src_pos]);
				}
				src_pos++;
			}

			if (src_pos < ldns_rdf_size(dname)) {
				ldns_buffer_printf(output, ".");
			}
			len = data[src_pos];
		}
	}
	return ldns_buffer_status(output);
}
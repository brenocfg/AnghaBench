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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int LDNS_APL_IP4 ; 
 int LDNS_APL_IP6 ; 
 int LDNS_APL_MASK ; 
 int LDNS_APL_NEGATION ; 
 int /*<<< orphan*/  LDNS_STATUS_WIRE_RDATA_ERR ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int ldns_read_uint16 (int*) ; 

ldns_status
ldns_rdf2buffer_str_apl(ldns_buffer *output, const ldns_rdf *rdf)
{
	uint8_t *data = ldns_rdf_data(rdf);
	uint16_t address_family;
	uint8_t prefix;
	bool negation;
	uint8_t adf_length;
	size_t i;
	size_t pos = 0;

	while (pos < (unsigned int) ldns_rdf_size(rdf)) {
                if(pos + 3 >= (unsigned)ldns_rdf_size(rdf))
                        return LDNS_STATUS_WIRE_RDATA_ERR;
		address_family = ldns_read_uint16(&data[pos]);
		prefix = data[pos + 2];
		negation = data[pos + 3] & LDNS_APL_NEGATION;
		adf_length = data[pos + 3] & LDNS_APL_MASK;
		if (address_family == LDNS_APL_IP4) {
			/* check if prefix < 32? */
			if (negation) {
				ldns_buffer_printf(output, "!");
			}
			ldns_buffer_printf(output, "%u:", address_family);
			/* address is variable length 0 - 4 */
			for (i = 0; i < 4; i++) {
				if (i > 0) {
					ldns_buffer_printf(output, ".");
				}
				if (i < (unsigned short) adf_length) {
                                        if(pos+i+4 >= ldns_rdf_size(rdf))
					    return LDNS_STATUS_WIRE_RDATA_ERR;
					ldns_buffer_printf(output, "%d",
					                   data[pos + i + 4]);
				} else {
					ldns_buffer_printf(output, "0");
				}
			}
			ldns_buffer_printf(output, "/%u ", prefix);
		} else if (address_family == LDNS_APL_IP6) {
			/* check if prefix < 128? */
			if (negation) {
				ldns_buffer_printf(output, "!");
			}
			ldns_buffer_printf(output, "%u:", address_family);
			/* address is variable length 0 - 16 */
			for (i = 0; i < 16; i++) {
				if (i % 2 == 0 && i > 0) {
					ldns_buffer_printf(output, ":");
				}
				if (i < (unsigned short) adf_length) {
                                        if(pos+i+4 >= ldns_rdf_size(rdf))
					    return LDNS_STATUS_WIRE_RDATA_ERR;
					ldns_buffer_printf(output, "%02x",
					                   data[pos + i + 4]);
				} else {
					ldns_buffer_printf(output, "00");
				}
			}
			ldns_buffer_printf(output, "/%u ", prefix);

		} else {
			/* unknown address family */
			ldns_buffer_printf(output,
					"Unknown address family: %u data: ",
					address_family);
			for (i = 1; i < (unsigned short) (4 + adf_length); i++) {
                                if(pos+i >= ldns_rdf_size(rdf))
                                        return LDNS_STATUS_WIRE_RDATA_ERR;
				ldns_buffer_printf(output, "%02x", data[i]);
			}
		}
		pos += 4 + adf_length;
	}
	return ldns_buffer_status(output);
}
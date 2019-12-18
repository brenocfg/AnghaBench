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
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int LDNS_MAX_DOMAINLEN ; 
 int LDNS_MAX_LABELLEN ; 
 unsigned int LDNS_MAX_POINTERS ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_STATUS_DOMAINNAME_OVERFLOW ; 
 int /*<<< orphan*/  LDNS_STATUS_INVALID_POINTER ; 
 int /*<<< orphan*/  LDNS_STATUS_LABEL_OVERFLOW ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  LDNS_STATUS_PACKET_OVERFLOW ; 
 int /*<<< orphan*/  LDNS_STATUS_WIRE_RDATA_ERR ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,size_t,int*) ; 
 size_t ldns_read_uint16 (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

ldns_status
ldns_wire2dname(ldns_rdf **dname, const uint8_t *wire, size_t max, size_t *pos)
{
	uint8_t label_size;
	uint16_t pointer_target;
	uint8_t pointer_target_buf[2];
	size_t dname_pos = 0;
	size_t uncompressed_length = 0;
	size_t compression_pos = 0;
	uint8_t tmp_dname[LDNS_MAX_DOMAINLEN];
	unsigned int pointer_count = 0;

	if (pos == NULL) {
		return LDNS_STATUS_WIRE_RDATA_ERR;
	}
	if (*pos >= max) {
		return LDNS_STATUS_PACKET_OVERFLOW;
	}
	label_size = wire[*pos];
	while (label_size > 0) {
		/* compression */
		while (label_size >= 192) {
			if (compression_pos == 0) {
				compression_pos = *pos + 2;
			}

			pointer_count++;

			/* remove first two bits */
			if (*pos + 2 > max) {
				return LDNS_STATUS_PACKET_OVERFLOW;
			}
			pointer_target_buf[0] = wire[*pos] & 63;
			pointer_target_buf[1] = wire[*pos + 1];
			pointer_target = ldns_read_uint16(pointer_target_buf);

			if (pointer_target == 0) {
				return LDNS_STATUS_INVALID_POINTER;
			} else if (pointer_target >= max) {
				return LDNS_STATUS_INVALID_POINTER;
			} else if (pointer_count > LDNS_MAX_POINTERS) {
				return LDNS_STATUS_INVALID_POINTER;
			}
			*pos = pointer_target;
			label_size = wire[*pos];
		}
		if(label_size == 0)
			break; /* break from pointer to 0 byte */
		if (label_size > LDNS_MAX_LABELLEN) {
			return LDNS_STATUS_LABEL_OVERFLOW;
		}
		if (*pos + 1 + label_size > max) {
			return LDNS_STATUS_LABEL_OVERFLOW;
		}

		/* check space for labelcount itself */
		if (dname_pos + 1 > LDNS_MAX_DOMAINLEN) {
			return LDNS_STATUS_DOMAINNAME_OVERFLOW;
		}
		tmp_dname[dname_pos] = label_size;
		if (label_size > 0) {
			dname_pos++;
		}
		*pos = *pos + 1;
		if (dname_pos + label_size > LDNS_MAX_DOMAINLEN) {
			return LDNS_STATUS_DOMAINNAME_OVERFLOW;
		}
		memcpy(&tmp_dname[dname_pos], &wire[*pos], label_size);
		uncompressed_length += label_size + 1;
		dname_pos += label_size;
		*pos = *pos + label_size;

		if (*pos < max) {
			label_size = wire[*pos];
		}
	}

	if (compression_pos > 0) {
		*pos = compression_pos;
	} else {
		*pos = *pos + 1;
	}

	if (dname_pos >= LDNS_MAX_DOMAINLEN) {
		return LDNS_STATUS_DOMAINNAME_OVERFLOW;
	}

	tmp_dname[dname_pos] = 0;
	dname_pos++;

	*dname = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_DNAME,
			(uint16_t) dname_pos, tmp_dname);
	if (!*dname) {
		return LDNS_STATUS_MEM_ERR;
	}
	return LDNS_STATUS_OK;
}
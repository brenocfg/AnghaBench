#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
struct TYPE_9__ {int _position; } ;
typedef  TYPE_1__ ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_WIRE_RDATA_ERR ; 
 int ldns_b64_ntop (scalar_t__*,size_t,char*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_b64_ntop_calculate_size (size_t) ; 
 scalar_t__ ldns_buffer_current (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_buffer_printf (TYPE_1__*,char*,int) ; 
 scalar_t__ ldns_buffer_remaining (TYPE_1__*) ; 
 scalar_t__ ldns_buffer_reserve (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_status (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_buffer_write_u8 (TYPE_1__*,scalar_t__) ; 
 scalar_t__* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 size_t ldns_read_uint16 (scalar_t__*) ; 

ldns_status
ldns_rdf2buffer_str_hip(ldns_buffer *output, const ldns_rdf *rdf)
{
	uint8_t *data = ldns_rdf_data(rdf);
	size_t rdf_size = ldns_rdf_size(rdf);
	uint8_t hit_size;
	uint16_t pk_size;
	int written;
	
	if (rdf_size < 6) {
		return LDNS_STATUS_WIRE_RDATA_ERR;
	}
	if ((hit_size = data[0]) == 0 ||
			(pk_size = ldns_read_uint16(data + 2)) == 0 ||
			rdf_size < (size_t) hit_size + pk_size + 4) {

		return LDNS_STATUS_WIRE_RDATA_ERR;
	}

	ldns_buffer_printf(output, "%d ", (int) data[1]);

	for (data += 4; hit_size > 0; hit_size--, data++) {

		ldns_buffer_printf(output, "%02x", (int) *data);
	}
	ldns_buffer_write_u8(output, (uint8_t) ' ');

	if (ldns_buffer_reserve(output,
				ldns_b64_ntop_calculate_size(pk_size))) {

		written = ldns_b64_ntop(data, pk_size,
				(char *) ldns_buffer_current(output),
				ldns_buffer_remaining(output));

		if (written > 0 &&
				written < (int) ldns_buffer_remaining(output)) {

			output->_position += written;
		}
	}
	return ldns_buffer_status(output);
}
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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_buffer_export (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 size_t ldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

ldns_status
ldns_rr2wire(uint8_t **dest, const ldns_rr *rr, int section, size_t *result_size)
{
	ldns_buffer *buffer = ldns_buffer_new(LDNS_MAX_PACKETLEN);
	ldns_status status;
	*result_size = 0;
	*dest = NULL;
	if(!buffer) return LDNS_STATUS_MEM_ERR;
	
	status = ldns_rr2buffer_wire(buffer, rr, section);
	if (status == LDNS_STATUS_OK) {
		*result_size =  ldns_buffer_position(buffer);
		*dest = (uint8_t *) ldns_buffer_export(buffer);
	}
	ldns_buffer_free(buffer);
	return status;
}
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
typedef  int /*<<< orphan*/  ldns_pkt_opcode ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_OK ; 
 char* ldns_buffer_export2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int) ; 
 scalar_t__ ldns_pkt_opcode2buffer_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *
ldns_pkt_opcode2str(ldns_pkt_opcode opcode)
{
	char *str;
	ldns_buffer *buf;

	buf = ldns_buffer_new(12);
	if (!buf) {
		return NULL;
	}

	str = NULL;
	if (ldns_pkt_opcode2buffer_str(buf, opcode) == LDNS_STATUS_OK) {
		str = ldns_buffer_export2str(buf);
	}

	ldns_buffer_free(buf);
	return str;
}
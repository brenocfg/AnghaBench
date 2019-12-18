#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  _answerfrom; int /*<<< orphan*/  _edns_data; int /*<<< orphan*/  _tsig_rr; int /*<<< orphan*/  _additional; int /*<<< orphan*/  _authority; int /*<<< orphan*/  _answer; int /*<<< orphan*/  _question; struct TYPE_4__* _header; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ ) ; 

void
ldns_pkt_free(ldns_pkt *packet)
{
	if (packet) {
		LDNS_FREE(packet->_header);
		ldns_rr_list_deep_free(packet->_question);
		ldns_rr_list_deep_free(packet->_answer);
		ldns_rr_list_deep_free(packet->_authority);
		ldns_rr_list_deep_free(packet->_additional);
		ldns_rr_free(packet->_tsig_rr);
		ldns_rdf_deep_free(packet->_edns_data);
		ldns_rdf_deep_free(packet->_answerfrom);
		LDNS_FREE(packet);
	}
}
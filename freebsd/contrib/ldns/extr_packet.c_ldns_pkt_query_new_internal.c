#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
struct TYPE_7__ {int /*<<< orphan*/ * _tsig_rr; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  LDNS_SECTION_QUESTION ; 
 int /*<<< orphan*/  ldns_pkt_free (TYPE_1__*) ; 
 TYPE_1__* ldns_pkt_new () ; 
 int /*<<< orphan*/  ldns_pkt_push_rr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_new () ; 
 int /*<<< orphan*/  ldns_rr_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_question (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ldns_pkt *
ldns_pkt_query_new_internal(ldns_rdf *rr_name, ldns_rr_type rr_type,
	ldns_rr_class rr_class,	uint16_t flags, ldns_rr* authsoa_rr)
{
	ldns_pkt *packet;
	ldns_rr *question_rr;

	packet = ldns_pkt_new();
	if (!packet) {
		return NULL;
	}

	if (!ldns_pkt_set_flags(packet, flags)) {
		return NULL;
	}

	question_rr = ldns_rr_new();
	if (!question_rr) {
		ldns_pkt_free(packet);
		return NULL;
	}

	if (rr_type == 0) {
		rr_type = LDNS_RR_TYPE_A;
	}
	if (rr_class == 0) {
		rr_class = LDNS_RR_CLASS_IN;
	}

	ldns_rr_set_owner(question_rr, rr_name);
	ldns_rr_set_type(question_rr, rr_type);
	ldns_rr_set_class(question_rr, rr_class);
        ldns_rr_set_question(question_rr, true);
	ldns_pkt_push_rr(packet, LDNS_SECTION_QUESTION, question_rr);

	if (authsoa_rr) {
		ldns_pkt_push_rr(packet, LDNS_SECTION_AUTHORITY, authsoa_rr);
	}

	packet->_tsig_rr = NULL;
	return packet;
}
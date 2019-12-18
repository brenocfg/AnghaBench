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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int ldns_dane_transport ;

/* Variables and functions */
#define  LDNS_DANE_TRANSPORT_SCTP 130 
#define  LDNS_DANE_TRANSPORT_TCP 129 
#define  LDNS_DANE_TRANSPORT_UDP 128 
 int LDNS_MAX_DOMAINLEN ; 
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_STATUS_DANE_UNKNOWN_TRANSPORT ; 
 int /*<<< orphan*/  LDNS_STATUS_DOMAINNAME_OVERFLOW ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (scalar_t__,int,char*) ; 
 int ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 

ldns_status
ldns_dane_create_tlsa_owner(ldns_rdf** tlsa_owner, const ldns_rdf* name,
		uint16_t port, ldns_dane_transport transport)
{
	char buf[LDNS_MAX_DOMAINLEN];
	size_t s;

	assert(tlsa_owner != NULL);
	assert(name != NULL);
	assert(ldns_rdf_get_type(name) == LDNS_RDF_TYPE_DNAME);

	s = (size_t)snprintf(buf, LDNS_MAX_DOMAINLEN, "X_%d", (int)port);
	buf[0] = (char)(s - 1);

	switch(transport) {
	case LDNS_DANE_TRANSPORT_TCP:
		s += snprintf(buf + s, LDNS_MAX_DOMAINLEN - s, "\004_tcp");
		break;
	
	case LDNS_DANE_TRANSPORT_UDP:
		s += snprintf(buf + s, LDNS_MAX_DOMAINLEN - s, "\004_udp");
		break;

	case LDNS_DANE_TRANSPORT_SCTP:
		s += snprintf(buf + s, LDNS_MAX_DOMAINLEN - s, "\005_sctp");
		break;
	
	default:
		return LDNS_STATUS_DANE_UNKNOWN_TRANSPORT;
	}
	if (s + ldns_rdf_size(name) > LDNS_MAX_DOMAINLEN) {
		return LDNS_STATUS_DOMAINNAME_OVERFLOW;
	}
	memcpy(buf + s, ldns_rdf_data(name), ldns_rdf_size(name));
	*tlsa_owner = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_DNAME,
			s + ldns_rdf_size(name), buf);
	if (*tlsa_owner == NULL) {
		return LDNS_STATUS_MEM_ERR;
	}
	return LDNS_STATUS_OK;
}
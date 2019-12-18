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
typedef  int sldns_rdf_type ;

/* Variables and functions */
#define  LDNS_RDF_TYPE_B64 133 
#define  LDNS_RDF_TYPE_HEX 132 
#define  LDNS_RDF_TYPE_IPSECKEY 131 
#define  LDNS_RDF_TYPE_LOC 130 
#define  LDNS_RDF_TYPE_NSEC 129 
#define  LDNS_RDF_TYPE_WKS 128 

__attribute__((used)) static const char*
rrinternal_get_delims(sldns_rdf_type rdftype, size_t r_cnt, size_t r_max)
{
	switch(rdftype) {
	case LDNS_RDF_TYPE_B64        :
	case LDNS_RDF_TYPE_HEX        : /* These rdf types may con- */
	case LDNS_RDF_TYPE_LOC        : /* tain whitespace, only if */
	case LDNS_RDF_TYPE_WKS        : /* it is the last rd field. */
	case LDNS_RDF_TYPE_IPSECKEY   :
	case LDNS_RDF_TYPE_NSEC       :	if (r_cnt == r_max - 1) {
						return "\n";
					}
					break;
	default                       :	break;
	}
	return "\n\t "; 
}
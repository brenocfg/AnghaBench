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
#define  LDNS_RDF_TYPE_A 139 
#define  LDNS_RDF_TYPE_AAAA 138 
#define  LDNS_RDF_TYPE_ALG 137 
#define  LDNS_RDF_TYPE_CERT_ALG 136 
#define  LDNS_RDF_TYPE_CLASS 135 
#define  LDNS_RDF_TYPE_INT16 134 
#define  LDNS_RDF_TYPE_INT32 133 
#define  LDNS_RDF_TYPE_INT8 132 
#define  LDNS_RDF_TYPE_PERIOD 131 
#define  LDNS_RDF_TYPE_TIME 130 
#define  LDNS_RDF_TYPE_TSIGTIME 129 
#define  LDNS_RDF_TYPE_TYPE 128 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

size_t
get_rdf_size(sldns_rdf_type rdf)
{
	switch(rdf) {
		case LDNS_RDF_TYPE_CLASS:
		case LDNS_RDF_TYPE_ALG:
		case LDNS_RDF_TYPE_INT8:
			return 1;
			break;
		case LDNS_RDF_TYPE_INT16:
		case LDNS_RDF_TYPE_TYPE:
		case LDNS_RDF_TYPE_CERT_ALG:
			return 2;
			break;
		case LDNS_RDF_TYPE_INT32:
		case LDNS_RDF_TYPE_TIME:
		case LDNS_RDF_TYPE_A:
		case LDNS_RDF_TYPE_PERIOD:
			return 4;
			break;
		case LDNS_RDF_TYPE_TSIGTIME:
			return 6;
			break;
		case LDNS_RDF_TYPE_AAAA:
			return 16;
			break;
		default:
			log_assert(0); /* add type above */
			/* only types that appear before a domain  *
			 * name are needed. rest is simply copied. */
	}
	return 0;
}
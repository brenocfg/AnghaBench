#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct packed_rrset_data {int* rr_len; scalar_t__** rr_data; } ;
struct TYPE_3__ {scalar_t__* _wireformat; scalar_t__ _dname_count; } ;
typedef  TYPE_1__ sldns_rr_descriptor ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ LDNS_RDF_TYPE_STR ; 
 int get_rdf_size (scalar_t__) ; 
 int memcmp (scalar_t__*,scalar_t__*,size_t) ; 
 scalar_t__ tolower (int) ; 

__attribute__((used)) static int
canonical_compare_byfield(struct packed_rrset_data* d, 
	const sldns_rr_descriptor* desc, size_t i, size_t j)
{
	/* sweep across rdata, keep track of some state:
	 * 	which rr field, and bytes left in field.
	 * 	current position in rdata, length left.
	 * 	are we in a dname, length left in a label.
	 */
	int wfi = -1;	/* current wireformat rdata field (rdf) */
	int wfj = -1;
	uint8_t* di = d->rr_data[i]+2; /* ptr to current rdata byte */
	uint8_t* dj = d->rr_data[j]+2;
	size_t ilen = d->rr_len[i]-2; /* length left in rdata */
	size_t jlen = d->rr_len[j]-2;
	int dname_i = 0;  /* true if these bytes are part of a name */
	int dname_j = 0;
	size_t lablen_i = 0; /* 0 for label length byte,for first byte of rdf*/
	size_t lablen_j = 0; /* otherwise remaining length of rdf or label */
	int dname_num_i = (int)desc->_dname_count; /* decreased at root label */
	int dname_num_j = (int)desc->_dname_count;

	/* loop while there are rdata bytes available for both rrs,
	 * and still some lowercasing needs to be done; either the dnames
	 * have not been reached yet, or they are currently being processed */
	while(ilen > 0 && jlen > 0 && (dname_num_i > 0 || dname_num_j > 0)) {
		/* compare these two bytes */
		/* lowercase if in a dname and not a label length byte */
		if( ((dname_i && lablen_i)?(uint8_t)tolower((int)*di):*di)
		 != ((dname_j && lablen_j)?(uint8_t)tolower((int)*dj):*dj)
		 ) {
		  if(((dname_i && lablen_i)?(uint8_t)tolower((int)*di):*di)
		  < ((dname_j && lablen_j)?(uint8_t)tolower((int)*dj):*dj))
		 	return -1;
		    return 1;
		}
		ilen--;
		jlen--;
		/* bytes are equal */

		/* advance field i */
		/* lablen 0 means that this byte is the first byte of the
		 * next rdata field; inspect this rdata field and setup
		 * to process the rest of this rdata field.
		 * The reason to first read the byte, then setup the rdf,
		 * is that we are then sure the byte is available and short
		 * rdata is handled gracefully (even if it is a formerr). */
		if(lablen_i == 0) { 
			if(dname_i) {
				/* scan this dname label */
				/* capture length to lowercase */
				lablen_i = (size_t)*di;
				if(lablen_i == 0) {
					/* end root label */
					dname_i = 0;
					dname_num_i--;
					/* if dname num is 0, then the
					 * remainder is binary only */
					if(dname_num_i == 0)
						lablen_i = ilen;
				}
			} else {
				/* scan this rdata field */
				wfi++;
				if(desc->_wireformat[wfi] 
					== LDNS_RDF_TYPE_DNAME) {
					dname_i = 1; 
					lablen_i = (size_t)*di;
					if(lablen_i == 0) {
						dname_i = 0;
						dname_num_i--;
						if(dname_num_i == 0)
							lablen_i = ilen;
					}
				} else if(desc->_wireformat[wfi] 
					== LDNS_RDF_TYPE_STR)
					lablen_i = (size_t)*di;
				else	lablen_i = get_rdf_size(
					desc->_wireformat[wfi]) - 1;
			}
		} else	lablen_i--;

		/* advance field j; same as for i */
		if(lablen_j == 0) { 
			if(dname_j) {
				lablen_j = (size_t)*dj;
				if(lablen_j == 0) {
					dname_j = 0;
					dname_num_j--;
					if(dname_num_j == 0)
						lablen_j = jlen;
				}
			} else {
				wfj++;
				if(desc->_wireformat[wfj] 
					== LDNS_RDF_TYPE_DNAME) {
					dname_j = 1; 
					lablen_j = (size_t)*dj;
					if(lablen_j == 0) {
						dname_j = 0;
						dname_num_j--;
						if(dname_num_j == 0)
							lablen_j = jlen;
					}
				} else if(desc->_wireformat[wfj] 
					== LDNS_RDF_TYPE_STR)
					lablen_j = (size_t)*dj;
				else	lablen_j = get_rdf_size(
					desc->_wireformat[wfj]) - 1;
			}
		} else	lablen_j--;
		di++;
		dj++;
	}
	/* end of the loop; because we advanced byte by byte; now we have
	 * that the rdata has ended, or that there is a binary remainder */
	/* shortest first */
	if(ilen == 0 && jlen == 0)
		return 0;
	if(ilen == 0)
		return -1;
	if(jlen == 0)
		return 1;
	/* binary remainder, capture comparison in wfi variable */
	if((wfi = memcmp(di, dj, (ilen<jlen)?ilen:jlen)) != 0)
		return wfi;
	if(ilen < jlen)
		return -1;
	if(jlen < ilen)
		return 1;
	return 0;
}
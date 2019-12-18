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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sldns_rr_descriptor ;
typedef  int /*<<< orphan*/  sldns_rdf_type ;

/* Variables and functions */
 int /*<<< orphan*/ * sldns_rr_descript (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_rr_descriptor_field_type (int /*<<< orphan*/  const*,size_t) ; 
 size_t sldns_rr_descriptor_maximum (int /*<<< orphan*/  const*) ; 
 size_t sldns_rr_descriptor_minimum (int /*<<< orphan*/  const*) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*) ; 
 int sldns_wire2str_rdata_unknown_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_rdf_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int sldns_wire2str_rdata_scan(uint8_t** d, size_t* dlen, char** s,
	size_t* slen, uint16_t rrtype, uint8_t* pkt, size_t pktlen)
{
	/* try to prettyprint, but if that fails, use unknown format */
	uint8_t* origd = *d;
	char* origs = *s;
	size_t origdlen = *dlen, origslen = *slen;
	size_t r_cnt, r_max;
	sldns_rdf_type rdftype;
	int w = 0, n;

	const sldns_rr_descriptor *desc = sldns_rr_descript(rrtype);
	if(!desc) /* unknown format */
		return sldns_wire2str_rdata_unknown_scan(d, dlen, s, slen);
	/* dlen equals the rdatalen for the rdata */

	r_max = sldns_rr_descriptor_maximum(desc);
	for(r_cnt=0; r_cnt < r_max; r_cnt++) {
		if(*dlen == 0) {
			if(r_cnt < sldns_rr_descriptor_minimum(desc))
				goto failed;
			break; /* nothing more to print */
		}
		rdftype = sldns_rr_descriptor_field_type(desc, r_cnt);
		if(r_cnt != 0)
			w += sldns_str_print(s, slen, " ");
		n = sldns_wire2str_rdf_scan(d, dlen, s, slen, rdftype,
			pkt, pktlen);
		if(n == -1) {
		failed:
			/* failed, use unknown format */
			*d = origd; *s = origs;
			*dlen = origdlen; *slen = origslen;
			return sldns_wire2str_rdata_unknown_scan(d, dlen,
				s, slen);
		}
		w += n;
	}
	if(*dlen != 0) {
		goto failed;
	}
	return w;
}
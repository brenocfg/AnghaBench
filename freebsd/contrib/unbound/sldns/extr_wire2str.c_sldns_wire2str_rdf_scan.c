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

/* Variables and functions */
#define  LDNS_RDF_TYPE_A 164 
#define  LDNS_RDF_TYPE_AAAA 163 
#define  LDNS_RDF_TYPE_ALG 162 
#define  LDNS_RDF_TYPE_APL 161 
#define  LDNS_RDF_TYPE_ATMA 160 
#define  LDNS_RDF_TYPE_B32_EXT 159 
#define  LDNS_RDF_TYPE_B64 158 
#define  LDNS_RDF_TYPE_CERT_ALG 157 
#define  LDNS_RDF_TYPE_CLASS 156 
#define  LDNS_RDF_TYPE_DNAME 155 
#define  LDNS_RDF_TYPE_EUI48 154 
#define  LDNS_RDF_TYPE_EUI64 153 
#define  LDNS_RDF_TYPE_HEX 152 
#define  LDNS_RDF_TYPE_HIP 151 
#define  LDNS_RDF_TYPE_ILNP64 150 
#define  LDNS_RDF_TYPE_INT16 149 
#define  LDNS_RDF_TYPE_INT16_DATA 148 
#define  LDNS_RDF_TYPE_INT32 147 
#define  LDNS_RDF_TYPE_INT8 146 
#define  LDNS_RDF_TYPE_IPSECKEY 145 
#define  LDNS_RDF_TYPE_LOC 144 
#define  LDNS_RDF_TYPE_LONG_STR 143 
#define  LDNS_RDF_TYPE_NONE 142 
#define  LDNS_RDF_TYPE_NSAP 141 
#define  LDNS_RDF_TYPE_NSEC 140 
#define  LDNS_RDF_TYPE_NSEC3_NEXT_OWNER 139 
#define  LDNS_RDF_TYPE_NSEC3_SALT 138 
#define  LDNS_RDF_TYPE_PERIOD 137 
#define  LDNS_RDF_TYPE_SERVICE 136 
#define  LDNS_RDF_TYPE_STR 135 
#define  LDNS_RDF_TYPE_TAG 134 
#define  LDNS_RDF_TYPE_TIME 133 
#define  LDNS_RDF_TYPE_TSIGERROR 132 
#define  LDNS_RDF_TYPE_TSIGTIME 131 
#define  LDNS_RDF_TYPE_TYPE 130 
#define  LDNS_RDF_TYPE_UNKNOWN 129 
#define  LDNS_RDF_TYPE_WKS 128 
 int sldns_wire2str_a_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_aaaa_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_alg_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_apl_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_atma_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_b32_ext_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_b64_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_cert_alg_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_class_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_dname_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_eui48_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_eui64_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_hex_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_hip_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_ilnp64_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_int16_data_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_int16_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_int32_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_int8_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_ipseckey_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_loc_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_long_str_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_nsap_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_nsec3_salt_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_nsec_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_period_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_str_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_tag_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_time_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_tsigerror_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_tsigtime_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_type_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_unknown_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_wire2str_wks_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 

int sldns_wire2str_rdf_scan(uint8_t** d, size_t* dlen, char** s, size_t* slen,
	int rdftype, uint8_t* pkt, size_t pktlen)
{
	if(*dlen == 0) return 0;
	switch(rdftype) {
	case LDNS_RDF_TYPE_NONE:
		return 0;
	case LDNS_RDF_TYPE_DNAME:
		return sldns_wire2str_dname_scan(d, dlen, s, slen, pkt, pktlen);
	case LDNS_RDF_TYPE_INT8:
		return sldns_wire2str_int8_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_INT16:
		return sldns_wire2str_int16_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_INT32:
		return sldns_wire2str_int32_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_PERIOD:
		return sldns_wire2str_period_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_TSIGTIME:
		return sldns_wire2str_tsigtime_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_A:
		return sldns_wire2str_a_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_AAAA:
		return sldns_wire2str_aaaa_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_STR:
		return sldns_wire2str_str_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_APL:
		return sldns_wire2str_apl_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_B32_EXT:
		return sldns_wire2str_b32_ext_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_B64:
		return sldns_wire2str_b64_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_HEX:
		return sldns_wire2str_hex_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_NSEC:
		return sldns_wire2str_nsec_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_NSEC3_SALT:
		return sldns_wire2str_nsec3_salt_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_TYPE:
		return sldns_wire2str_type_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_CLASS:
		return sldns_wire2str_class_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_CERT_ALG:
		return sldns_wire2str_cert_alg_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_ALG:
		return sldns_wire2str_alg_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_UNKNOWN:
		return sldns_wire2str_unknown_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_TIME:
		return sldns_wire2str_time_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_LOC:
		return sldns_wire2str_loc_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_WKS:
	case LDNS_RDF_TYPE_SERVICE:
		return sldns_wire2str_wks_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_NSAP:
		return sldns_wire2str_nsap_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_ATMA:
		return sldns_wire2str_atma_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_IPSECKEY:
		return sldns_wire2str_ipseckey_scan(d, dlen, s, slen, pkt,
			pktlen);
	case LDNS_RDF_TYPE_HIP:
		return sldns_wire2str_hip_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_INT16_DATA:
		return sldns_wire2str_int16_data_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_NSEC3_NEXT_OWNER:
		return sldns_wire2str_b32_ext_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_ILNP64:
		return sldns_wire2str_ilnp64_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_EUI48:
		return sldns_wire2str_eui48_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_EUI64:
		return sldns_wire2str_eui64_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_TAG:
		return sldns_wire2str_tag_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_LONG_STR:
		return sldns_wire2str_long_str_scan(d, dlen, s, slen);
	case LDNS_RDF_TYPE_TSIGERROR:
		return sldns_wire2str_tsigerror_scan(d, dlen, s, slen);
	}
	/* unknown rdf type */
	return -1;
}
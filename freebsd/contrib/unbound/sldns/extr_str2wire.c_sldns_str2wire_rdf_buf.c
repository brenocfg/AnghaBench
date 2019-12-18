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
typedef  int sldns_rdf_type ;

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
 int LDNS_WIREPARSE_ERR_GENERAL ; 
 int LDNS_WIREPARSE_ERR_NOT_IMPL ; 
 int sldns_str2wire_a_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_aaaa_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_alg_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_apl_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_atma_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_b32_ext_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_b64_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_cert_alg_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_class_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_dname_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_eui48_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_eui64_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_hex_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_hip_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_ilnp64_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_int16_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_int16_data_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_int32_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_int8_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_ipseckey_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_loc_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_long_str_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_nsap_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_nsec3_salt_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_nsec_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_period_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_str_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_tag_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_time_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_tsigerror_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_tsigtime_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_type_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int sldns_str2wire_wks_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 

int sldns_str2wire_rdf_buf(const char* str, uint8_t* rd, size_t* len,
	sldns_rdf_type rdftype)
{
	switch (rdftype) {
	case LDNS_RDF_TYPE_DNAME:
		return sldns_str2wire_dname_buf(str, rd, len);
	case LDNS_RDF_TYPE_INT8:
		return sldns_str2wire_int8_buf(str, rd, len);
	case LDNS_RDF_TYPE_INT16:
		return sldns_str2wire_int16_buf(str, rd, len);
	case LDNS_RDF_TYPE_INT32:
		return sldns_str2wire_int32_buf(str, rd, len);
	case LDNS_RDF_TYPE_A:
		return sldns_str2wire_a_buf(str, rd, len);
	case LDNS_RDF_TYPE_AAAA:
		return sldns_str2wire_aaaa_buf(str, rd, len);
	case LDNS_RDF_TYPE_STR:
		return sldns_str2wire_str_buf(str, rd, len);
	case LDNS_RDF_TYPE_APL:
		return sldns_str2wire_apl_buf(str, rd, len);
	case LDNS_RDF_TYPE_B64:
		return sldns_str2wire_b64_buf(str, rd, len);
	case LDNS_RDF_TYPE_B32_EXT:
		return sldns_str2wire_b32_ext_buf(str, rd, len);
	case LDNS_RDF_TYPE_HEX:
		return sldns_str2wire_hex_buf(str, rd, len);
	case LDNS_RDF_TYPE_NSEC:
		return sldns_str2wire_nsec_buf(str, rd, len);
	case LDNS_RDF_TYPE_TYPE:
		return sldns_str2wire_type_buf(str, rd, len);
	case LDNS_RDF_TYPE_CLASS:
		return sldns_str2wire_class_buf(str, rd, len);
	case LDNS_RDF_TYPE_CERT_ALG:
		return sldns_str2wire_cert_alg_buf(str, rd, len);
	case LDNS_RDF_TYPE_ALG:
		return sldns_str2wire_alg_buf(str, rd, len);
	case LDNS_RDF_TYPE_TIME:
		return sldns_str2wire_time_buf(str, rd, len);
	case LDNS_RDF_TYPE_PERIOD:
		return sldns_str2wire_period_buf(str, rd, len);
	case LDNS_RDF_TYPE_TSIGTIME:
		return sldns_str2wire_tsigtime_buf(str, rd, len);
	case LDNS_RDF_TYPE_LOC:
		return sldns_str2wire_loc_buf(str, rd, len);
	case LDNS_RDF_TYPE_WKS:
		return sldns_str2wire_wks_buf(str, rd, len);
	case LDNS_RDF_TYPE_NSAP:
		return sldns_str2wire_nsap_buf(str, rd, len);
	case LDNS_RDF_TYPE_ATMA:
		return sldns_str2wire_atma_buf(str, rd, len);
	case LDNS_RDF_TYPE_IPSECKEY:
		return sldns_str2wire_ipseckey_buf(str, rd, len);
	case LDNS_RDF_TYPE_NSEC3_SALT:
		return sldns_str2wire_nsec3_salt_buf(str, rd, len);
	case LDNS_RDF_TYPE_NSEC3_NEXT_OWNER:
		return sldns_str2wire_b32_ext_buf(str, rd, len);
	case LDNS_RDF_TYPE_ILNP64:
		return sldns_str2wire_ilnp64_buf(str, rd, len);
	case LDNS_RDF_TYPE_EUI48:
		return sldns_str2wire_eui48_buf(str, rd, len);
	case LDNS_RDF_TYPE_EUI64:
		return sldns_str2wire_eui64_buf(str, rd, len);
	case LDNS_RDF_TYPE_TAG:
		return sldns_str2wire_tag_buf(str, rd, len);
	case LDNS_RDF_TYPE_LONG_STR:
		return sldns_str2wire_long_str_buf(str, rd, len);
	case LDNS_RDF_TYPE_TSIGERROR:
		return sldns_str2wire_tsigerror_buf(str, rd, len);
	case LDNS_RDF_TYPE_HIP:
		return sldns_str2wire_hip_buf(str, rd, len);
	case LDNS_RDF_TYPE_INT16_DATA:
		return sldns_str2wire_int16_data_buf(str, rd, len);
	case LDNS_RDF_TYPE_UNKNOWN:
	case LDNS_RDF_TYPE_SERVICE:
		return LDNS_WIREPARSE_ERR_NOT_IMPL;
	case LDNS_RDF_TYPE_NONE:
	default:
		break;
	}
	return LDNS_WIREPARSE_ERR_GENERAL;
}
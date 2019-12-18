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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_output_format ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
#define  LDNS_RDF_TYPE_A 166 
#define  LDNS_RDF_TYPE_AAAA 165 
#define  LDNS_RDF_TYPE_ALG 164 
#define  LDNS_RDF_TYPE_APL 163 
#define  LDNS_RDF_TYPE_ATMA 162 
#define  LDNS_RDF_TYPE_B32_EXT 161 
#define  LDNS_RDF_TYPE_B64 160 
#define  LDNS_RDF_TYPE_CERTIFICATE_USAGE 159 
#define  LDNS_RDF_TYPE_CERT_ALG 158 
#define  LDNS_RDF_TYPE_CLASS 157 
#define  LDNS_RDF_TYPE_DNAME 156 
#define  LDNS_RDF_TYPE_EUI48 155 
#define  LDNS_RDF_TYPE_EUI64 154 
#define  LDNS_RDF_TYPE_HEX 153 
#define  LDNS_RDF_TYPE_HIP 152 
#define  LDNS_RDF_TYPE_ILNP64 151 
#define  LDNS_RDF_TYPE_INT16 150 
#define  LDNS_RDF_TYPE_INT16_DATA 149 
#define  LDNS_RDF_TYPE_INT32 148 
#define  LDNS_RDF_TYPE_INT8 147 
#define  LDNS_RDF_TYPE_IPSECKEY 146 
#define  LDNS_RDF_TYPE_LOC 145 
#define  LDNS_RDF_TYPE_LONG_STR 144 
#define  LDNS_RDF_TYPE_MATCHING_TYPE 143 
#define  LDNS_RDF_TYPE_NONE 142 
#define  LDNS_RDF_TYPE_NSAP 141 
#define  LDNS_RDF_TYPE_NSEC 140 
#define  LDNS_RDF_TYPE_NSEC3_NEXT_OWNER 139 
#define  LDNS_RDF_TYPE_NSEC3_SALT 138 
#define  LDNS_RDF_TYPE_PERIOD 137 
#define  LDNS_RDF_TYPE_SELECTOR 136 
#define  LDNS_RDF_TYPE_SERVICE 135 
#define  LDNS_RDF_TYPE_STR 134 
#define  LDNS_RDF_TYPE_TAG 133 
#define  LDNS_RDF_TYPE_TIME 132 
#define  LDNS_RDF_TYPE_TSIGTIME 131 
#define  LDNS_RDF_TYPE_TYPE 130 
#define  LDNS_RDF_TYPE_UNKNOWN 129 
#define  LDNS_RDF_TYPE_WKS 128 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_a (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_aaaa (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_apl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_atma (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_b32_ext (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_b64 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_cert_alg (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_class (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_dname (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_eui48 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_eui64 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_hex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_hip (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_ilnp64 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_int16_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_ipseckey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_loc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_long_str (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_nsap (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_nsec3_salt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_nsec_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_period (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_str (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_tag (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_time (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_tsigtime (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_type_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_unknown (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str_wks (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ldns_status
ldns_rdf2buffer_str_fmt(ldns_buffer *buffer,
		const ldns_output_format* fmt, const ldns_rdf *rdf)
{
	ldns_status res = LDNS_STATUS_OK;

	/*ldns_buffer_printf(buffer, "%u:", ldns_rdf_get_type(rdf));*/
	if (rdf) {
		switch(ldns_rdf_get_type(rdf)) {
		case LDNS_RDF_TYPE_NONE:
			break;
		case LDNS_RDF_TYPE_DNAME:
			res = ldns_rdf2buffer_str_dname(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_INT8: /* Don't output mnemonics for these */
		case LDNS_RDF_TYPE_ALG:
		case LDNS_RDF_TYPE_CERTIFICATE_USAGE:
		case LDNS_RDF_TYPE_SELECTOR:
		case LDNS_RDF_TYPE_MATCHING_TYPE:
			res = ldns_rdf2buffer_str_int8(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_INT16:
			res = ldns_rdf2buffer_str_int16(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_INT32:
			res = ldns_rdf2buffer_str_int32(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_PERIOD:
			res = ldns_rdf2buffer_str_period(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_TSIGTIME:
			res = ldns_rdf2buffer_str_tsigtime(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_A:
			res = ldns_rdf2buffer_str_a(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_AAAA:
			res = ldns_rdf2buffer_str_aaaa(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_STR:
			res = ldns_rdf2buffer_str_str(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_APL:
			res = ldns_rdf2buffer_str_apl(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_B32_EXT:
			res = ldns_rdf2buffer_str_b32_ext(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_B64:
			res = ldns_rdf2buffer_str_b64(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_HEX:
			res = ldns_rdf2buffer_str_hex(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_NSEC:
			res = ldns_rdf2buffer_str_nsec_fmt(buffer, fmt, rdf);
			break;
		case LDNS_RDF_TYPE_NSEC3_SALT:
			res = ldns_rdf2buffer_str_nsec3_salt(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_TYPE:
			res = ldns_rdf2buffer_str_type_fmt(buffer, fmt, rdf);
			break;
		case LDNS_RDF_TYPE_CLASS:
			res = ldns_rdf2buffer_str_class(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_CERT_ALG:
			res = ldns_rdf2buffer_str_cert_alg(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_UNKNOWN:
			res = ldns_rdf2buffer_str_unknown(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_TIME:
			res = ldns_rdf2buffer_str_time(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_HIP:
			res = ldns_rdf2buffer_str_hip(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_LOC:
			res = ldns_rdf2buffer_str_loc(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_WKS:
		case LDNS_RDF_TYPE_SERVICE:
			res = ldns_rdf2buffer_str_wks(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_NSAP:
			res = ldns_rdf2buffer_str_nsap(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_ATMA:
			res = ldns_rdf2buffer_str_atma(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_IPSECKEY:
			res = ldns_rdf2buffer_str_ipseckey(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_INT16_DATA:
			res = ldns_rdf2buffer_str_int16_data(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_NSEC3_NEXT_OWNER:
			res = ldns_rdf2buffer_str_b32_ext(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_ILNP64:
			res = ldns_rdf2buffer_str_ilnp64(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_EUI48:
			res = ldns_rdf2buffer_str_eui48(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_EUI64:
			res = ldns_rdf2buffer_str_eui64(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_TAG:
			res = ldns_rdf2buffer_str_tag(buffer, rdf);
			break;
		case LDNS_RDF_TYPE_LONG_STR:
			res = ldns_rdf2buffer_str_long_str(buffer, rdf);
			break;
		}
	} else {
		/** This will write mangled RRs */
		ldns_buffer_printf(buffer, "(null) ");
		res = LDNS_STATUS_ERR;
	}
	return res;
}
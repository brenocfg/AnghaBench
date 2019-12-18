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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf_type ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
#define  LDNS_RDF_TYPE_A 164 
#define  LDNS_RDF_TYPE_AAAA 163 
#define  LDNS_RDF_TYPE_ALG 162 
#define  LDNS_RDF_TYPE_APL 161 
#define  LDNS_RDF_TYPE_ATMA 160 
#define  LDNS_RDF_TYPE_B32_EXT 159 
#define  LDNS_RDF_TYPE_B64 158 
#define  LDNS_RDF_TYPE_CERTIFICATE_USAGE 157 
#define  LDNS_RDF_TYPE_CERT_ALG 156 
#define  LDNS_RDF_TYPE_CLASS 155 
#define  LDNS_RDF_TYPE_DNAME 154 
#define  LDNS_RDF_TYPE_EUI48 153 
#define  LDNS_RDF_TYPE_EUI64 152 
#define  LDNS_RDF_TYPE_HEX 151 
#define  LDNS_RDF_TYPE_HIP 150 
#define  LDNS_RDF_TYPE_ILNP64 149 
#define  LDNS_RDF_TYPE_INT16 148 
#define  LDNS_RDF_TYPE_INT32 147 
#define  LDNS_RDF_TYPE_INT8 146 
#define  LDNS_RDF_TYPE_IPSECKEY 145 
#define  LDNS_RDF_TYPE_LOC 144 
#define  LDNS_RDF_TYPE_LONG_STR 143 
#define  LDNS_RDF_TYPE_MATCHING_TYPE 142 
#define  LDNS_RDF_TYPE_NONE 141 
#define  LDNS_RDF_TYPE_NSAP 140 
#define  LDNS_RDF_TYPE_NSEC 139 
#define  LDNS_RDF_TYPE_NSEC3_NEXT_OWNER 138 
#define  LDNS_RDF_TYPE_NSEC3_SALT 137 
#define  LDNS_RDF_TYPE_PERIOD 136 
#define  LDNS_RDF_TYPE_SELECTOR 135 
#define  LDNS_RDF_TYPE_SERVICE 134 
#define  LDNS_RDF_TYPE_STR 133 
#define  LDNS_RDF_TYPE_TAG 132 
#define  LDNS_RDF_TYPE_TIME 131 
#define  LDNS_RDF_TYPE_TYPE 130 
#define  LDNS_RDF_TYPE_UNKNOWN 129 
#define  LDNS_RDF_TYPE_WKS 128 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_rdf_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_str2rdf_a (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_aaaa (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_alg (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_apl (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_atma (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_b32_ext (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_b64 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_cert_alg (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_certificate_usage (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_class (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_dname (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_eui48 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_eui64 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_hex (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_hip (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_ilnp64 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_int16 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_int32 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_int8 (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_ipseckey (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_loc (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_long_str (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_matching_type (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_nsap (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_nsec (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_nsec3_salt (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_period (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_selector (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_service (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_str (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_tag (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_time (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_type (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_unknown (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ldns_str2rdf_wks (int /*<<< orphan*/ **,char const*) ; 

ldns_rdf *
ldns_rdf_new_frm_str(ldns_rdf_type type, const char *str)
{
	ldns_rdf *rdf = NULL;
	ldns_status status;

	switch (type) {
	case LDNS_RDF_TYPE_DNAME:
		status = ldns_str2rdf_dname(&rdf, str);
		break;
	case LDNS_RDF_TYPE_INT8:
		status = ldns_str2rdf_int8(&rdf, str);
		break;
	case LDNS_RDF_TYPE_INT16:
		status = ldns_str2rdf_int16(&rdf, str);
		break;
	case LDNS_RDF_TYPE_INT32:
		status = ldns_str2rdf_int32(&rdf, str);
		break;
	case LDNS_RDF_TYPE_A:
		status = ldns_str2rdf_a(&rdf, str);
		break;
	case LDNS_RDF_TYPE_AAAA:
		status = ldns_str2rdf_aaaa(&rdf, str);
		break;
	case LDNS_RDF_TYPE_STR:
		status = ldns_str2rdf_str(&rdf, str);
		break;
	case LDNS_RDF_TYPE_APL:
		status = ldns_str2rdf_apl(&rdf, str);
		break;
	case LDNS_RDF_TYPE_B64:
		status = ldns_str2rdf_b64(&rdf, str);
		break;
	case LDNS_RDF_TYPE_B32_EXT:
		status = ldns_str2rdf_b32_ext(&rdf, str);
		break;
	case LDNS_RDF_TYPE_HEX:
		status = ldns_str2rdf_hex(&rdf, str);
		break;
	case LDNS_RDF_TYPE_NSEC:
		status = ldns_str2rdf_nsec(&rdf, str);
		break;
	case LDNS_RDF_TYPE_TYPE:
		status = ldns_str2rdf_type(&rdf, str);
		break;
	case LDNS_RDF_TYPE_CLASS:
		status = ldns_str2rdf_class(&rdf, str);
		break;
	case LDNS_RDF_TYPE_CERT_ALG:
		status = ldns_str2rdf_cert_alg(&rdf, str);
		break;
	case LDNS_RDF_TYPE_ALG:
		status = ldns_str2rdf_alg(&rdf, str);
		break;
	case LDNS_RDF_TYPE_UNKNOWN:
		status = ldns_str2rdf_unknown(&rdf, str);
		break;
	case LDNS_RDF_TYPE_TIME:
		status = ldns_str2rdf_time(&rdf, str);
		break;
	case LDNS_RDF_TYPE_PERIOD:
		status = ldns_str2rdf_period(&rdf, str);
		break;
	case LDNS_RDF_TYPE_HIP:
		status = ldns_str2rdf_hip(&rdf, str);
		break;
	case LDNS_RDF_TYPE_SERVICE:
		status = ldns_str2rdf_service(&rdf, str);
		break;
	case LDNS_RDF_TYPE_LOC:
		status = ldns_str2rdf_loc(&rdf, str);
		break;
	case LDNS_RDF_TYPE_WKS:
		status = ldns_str2rdf_wks(&rdf, str);
		break;
	case LDNS_RDF_TYPE_NSAP:
		status = ldns_str2rdf_nsap(&rdf, str);
		break;
	case LDNS_RDF_TYPE_ATMA:
		status = ldns_str2rdf_atma(&rdf, str);
		break;
	case LDNS_RDF_TYPE_IPSECKEY:
		status = ldns_str2rdf_ipseckey(&rdf, str);
		break;
	case LDNS_RDF_TYPE_NSEC3_SALT:
		status = ldns_str2rdf_nsec3_salt(&rdf, str);
		break;
	case LDNS_RDF_TYPE_NSEC3_NEXT_OWNER:
		status = ldns_str2rdf_b32_ext(&rdf, str);
		break;
	case LDNS_RDF_TYPE_ILNP64:
		status = ldns_str2rdf_ilnp64(&rdf, str);
		break;
	case LDNS_RDF_TYPE_EUI48:
		status = ldns_str2rdf_eui48(&rdf, str);
		break;
	case LDNS_RDF_TYPE_EUI64:
		status = ldns_str2rdf_eui64(&rdf, str);
		break;
	case LDNS_RDF_TYPE_TAG:
		status = ldns_str2rdf_tag(&rdf, str);
		break;
	case LDNS_RDF_TYPE_LONG_STR:
		status = ldns_str2rdf_long_str(&rdf, str);
		break;
	case LDNS_RDF_TYPE_CERTIFICATE_USAGE:
		status = ldns_str2rdf_certificate_usage(&rdf, str);
		break;
	case LDNS_RDF_TYPE_SELECTOR:
		status = ldns_str2rdf_selector(&rdf, str);
		break;
	case LDNS_RDF_TYPE_MATCHING_TYPE:
		status = ldns_str2rdf_matching_type(&rdf, str);
		break;
	case LDNS_RDF_TYPE_NONE:
	default:
		/* default default ??? */
		status = LDNS_STATUS_ERR;
		break;
	}
	if (LDNS_STATUS_OK == status) {
		ldns_rdf_set_type(rdf, type);
		return rdf;
	}
	if (rdf) {
		LDNS_FREE(rdf);
	}
	return NULL;
}
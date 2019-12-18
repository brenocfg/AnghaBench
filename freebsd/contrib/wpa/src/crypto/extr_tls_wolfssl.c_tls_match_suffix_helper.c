#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WOLFSSL_X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  WOLFSSL_X509_NAME ;
typedef  int /*<<< orphan*/  WOLFSSL_X509 ;
struct TYPE_5__ {char const* data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ WOLFSSL_ASN1_STRING ;
struct TYPE_6__ {scalar_t__ type; char const* obj; } ;
typedef  TYPE_2__ WOLFSSL_ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ALT_NAMES_OID ; 
 int /*<<< orphan*/  ASN_COMMON_NAME ; 
 scalar_t__ ASN_DNS_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int domain_suffix_match (char const*,int /*<<< orphan*/ ,char const*,size_t,int) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 TYPE_1__* wolfSSL_X509_NAME_ENTRY_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wolfSSL_X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int wolfSSL_X509_NAME_get_index_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* wolfSSL_X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wolfSSL_X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_sk_ASN1_OBJECT_free (void*) ; 
 int wolfSSL_sk_num (void*) ; 
 TYPE_2__* wolfSSL_sk_value (void*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_match_suffix_helper(WOLFSSL_X509 *cert, const char *match,
				   size_t match_len, int full)
{
	WOLFSSL_ASN1_OBJECT *gen;
	void *ext;
	int i;
	int j;
	int dns_name = 0;
	WOLFSSL_X509_NAME *name;

	wpa_printf(MSG_DEBUG, "TLS: Match domain against %s%s",
		   full ? "" : "suffix ", match);

	ext = wolfSSL_X509_get_ext_d2i(cert, ALT_NAMES_OID, NULL, NULL);

	for (j = 0; ext && j < wolfSSL_sk_num(ext); j++) {
		gen = wolfSSL_sk_value(ext, j);
		if (gen->type != ASN_DNS_TYPE)
			continue;
		dns_name++;
		wpa_hexdump_ascii(MSG_DEBUG, "TLS: Certificate dNSName",
				  gen->obj, os_strlen((char *)gen->obj));
		if (domain_suffix_match((const char *) gen->obj,
					os_strlen((char *) gen->obj), match,
					match_len, full) == 1) {
			wpa_printf(MSG_DEBUG, "TLS: %s in dNSName found",
				   full ? "Match" : "Suffix match");
			wolfSSL_sk_ASN1_OBJECT_free(ext);
			return 1;
		}
	}
	wolfSSL_sk_ASN1_OBJECT_free(ext);

	if (dns_name) {
		wpa_printf(MSG_DEBUG, "TLS: None of the dNSName(s) matched");
		return 0;
	}

	name = wolfSSL_X509_get_subject_name(cert);
	i = -1;
	for (;;) {
		WOLFSSL_X509_NAME_ENTRY *e;
		WOLFSSL_ASN1_STRING *cn;

		i = wolfSSL_X509_NAME_get_index_by_NID(name, ASN_COMMON_NAME,
						       i);
		if (i == -1)
			break;
		e = wolfSSL_X509_NAME_get_entry(name, i);
		if (!e)
			continue;
		cn = wolfSSL_X509_NAME_ENTRY_get_data(e);
		if (!cn)
			continue;
		wpa_hexdump_ascii(MSG_DEBUG, "TLS: Certificate commonName",
				  cn->data, cn->length);
		if (domain_suffix_match(cn->data, cn->length,
					match, match_len, full) == 1) {
			wpa_printf(MSG_DEBUG, "TLS: %s in commonName found",
				   full ? "Match" : "Suffix match");
			return 1;
		}
	}

	wpa_printf(MSG_DEBUG, "TLS: No CommonName %smatch found",
		   full ? "" : "suffix ");
	return 0;
}
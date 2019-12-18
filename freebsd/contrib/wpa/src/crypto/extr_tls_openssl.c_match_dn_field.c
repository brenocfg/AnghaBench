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
struct tls_dn_field_order_cnt {int dummy; } ;
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int X509_NAME_get_index_by_NID (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int get_dn_field_index (struct tls_dn_field_order_cnt const*,int) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_dn_field(const X509 *cert, int nid, const char *field,
			  const char *value,
			  const struct tls_dn_field_order_cnt *dn_cnt)
{
	int i, ret = 0, len, config_dn_field_index, match_index = 0;
	X509_NAME *name;

	len = os_strlen(value);
	name = X509_get_subject_name((X509 *) cert);

	/* Assign incremented cnt for every field of DN to check DN field in
	 * right order */
	config_dn_field_index = get_dn_field_index(dn_cnt, nid);
	if (config_dn_field_index < 0)
		return 0;

	/* Fetch value based on NID */
	for (i = -1; (i = X509_NAME_get_index_by_NID(name, nid, i)) > -1;) {
		X509_NAME_ENTRY *e;
		ASN1_STRING *cn;

		e = X509_NAME_get_entry(name, i);
		if (!e)
			continue;

		cn = X509_NAME_ENTRY_get_data(e);
		if (!cn)
			continue;

		match_index++;

		/* check for more than one DN field with same name */
		if (match_index != config_dn_field_index)
			continue;

		/* Check wildcard at the right end side */
		/* E.g., if OU=develop* mentioned in configuration, allow 'OU'
		 * of the subject in the client certificate to start with
		 * 'develop' */
		if (len > 0 && value[len - 1] == '*') {
			/* Compare actual certificate DN field value with
			 * configuration DN field value up to the specified
			 * length. */
			ret = ASN1_STRING_length(cn) >= len - 1 &&
				os_memcmp(ASN1_STRING_get0_data(cn), value,
					  len - 1) == 0;
		} else {
			/* Compare actual certificate DN field value with
			 * configuration DN field value */
			ret = ASN1_STRING_length(cn) == len &&
				os_memcmp(ASN1_STRING_get0_data(cn), value,
					  len) == 0;
		}
		if (!ret) {
			wpa_printf(MSG_ERROR,
				   "OpenSSL: Failed to match %s '%s' with certificate DN field value '%s'",
				   field, value, ASN1_STRING_get0_data(cn));
		}
		break;
	}

	return ret;
}
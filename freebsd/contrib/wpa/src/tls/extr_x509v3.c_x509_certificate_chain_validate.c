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
struct x509_certificate {int issuer_trusted; int extensions_present; unsigned long path_len_constraint; int /*<<< orphan*/  subject; int /*<<< orphan*/  issuer; struct x509_certificate* next; scalar_t__ not_after; scalar_t__ not_before; } ;
struct os_time {scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int X509_EXT_PATH_LEN_CONSTRAINT ; 
 int X509_VALIDATE_BAD_CERTIFICATE ; 
 int X509_VALIDATE_CERTIFICATE_EXPIRED ; 
 int X509_VALIDATE_CERTIFICATE_UNKNOWN ; 
 int X509_VALIDATE_OK ; 
 int X509_VALIDATE_UNKNOWN_CA ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ x509_certificate_check_signature (struct x509_certificate*,struct x509_certificate*) ; 
 scalar_t__ x509_name_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_name_string (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ x509_valid_issuer (struct x509_certificate*) ; 

int x509_certificate_chain_validate(struct x509_certificate *trusted,
				    struct x509_certificate *chain,
				    int *reason, int disable_time_checks)
{
	long unsigned idx;
	int chain_trusted = 0;
	struct x509_certificate *cert, *trust;
	char buf[128];
	struct os_time now;

	*reason = X509_VALIDATE_OK;

	wpa_printf(MSG_DEBUG, "X509: Validate certificate chain");
	os_get_time(&now);

	for (cert = chain, idx = 0; cert; cert = cert->next, idx++) {
		cert->issuer_trusted = 0;
		x509_name_string(&cert->subject, buf, sizeof(buf));
		wpa_printf(MSG_DEBUG, "X509: %lu: %s", idx, buf);

		if (chain_trusted)
			continue;

		if (!disable_time_checks &&
		    ((unsigned long) now.sec <
		     (unsigned long) cert->not_before ||
		     (unsigned long) now.sec >
		     (unsigned long) cert->not_after)) {
			wpa_printf(MSG_INFO, "X509: Certificate not valid "
				   "(now=%lu not_before=%lu not_after=%lu)",
				   now.sec, cert->not_before, cert->not_after);
			*reason = X509_VALIDATE_CERTIFICATE_EXPIRED;
			return -1;
		}

		if (cert->next) {
			if (x509_name_compare(&cert->issuer,
					      &cert->next->subject) != 0) {
				wpa_printf(MSG_DEBUG, "X509: Certificate "
					   "chain issuer name mismatch");
				x509_name_string(&cert->issuer, buf,
						 sizeof(buf));
				wpa_printf(MSG_DEBUG, "X509: cert issuer: %s",
					   buf);
				x509_name_string(&cert->next->subject, buf,
						 sizeof(buf));
				wpa_printf(MSG_DEBUG, "X509: next cert "
					   "subject: %s", buf);
				*reason = X509_VALIDATE_CERTIFICATE_UNKNOWN;
				return -1;
			}

			if (x509_valid_issuer(cert->next) < 0) {
				*reason = X509_VALIDATE_BAD_CERTIFICATE;
				return -1;
			}

			if ((cert->next->extensions_present &
			     X509_EXT_PATH_LEN_CONSTRAINT) &&
			    idx > cert->next->path_len_constraint) {
				wpa_printf(MSG_DEBUG, "X509: pathLenConstraint"
					   " not met (idx=%lu issuer "
					   "pathLenConstraint=%lu)", idx,
					   cert->next->path_len_constraint);
				*reason = X509_VALIDATE_BAD_CERTIFICATE;
				return -1;
			}

			if (x509_certificate_check_signature(cert->next, cert)
			    < 0) {
				wpa_printf(MSG_DEBUG, "X509: Invalid "
					   "certificate signature within "
					   "chain");
				*reason = X509_VALIDATE_BAD_CERTIFICATE;
				return -1;
			}
		}

		for (trust = trusted; trust; trust = trust->next) {
			if (x509_name_compare(&cert->issuer, &trust->subject)
			    == 0)
				break;
		}

		if (trust) {
			wpa_printf(MSG_DEBUG, "X509: Found issuer from the "
				   "list of trusted certificates");
			if (x509_valid_issuer(trust) < 0) {
				*reason = X509_VALIDATE_BAD_CERTIFICATE;
				return -1;
			}

			if (x509_certificate_check_signature(trust, cert) < 0)
			{
				wpa_printf(MSG_DEBUG, "X509: Invalid "
					   "certificate signature");
				*reason = X509_VALIDATE_BAD_CERTIFICATE;
				return -1;
			}

			wpa_printf(MSG_DEBUG, "X509: Trusted certificate "
				   "found to complete the chain");
			cert->issuer_trusted = 1;
			chain_trusted = 1;
		}
	}

	if (!chain_trusted) {
		wpa_printf(MSG_DEBUG, "X509: Did not find any of the issuers "
			   "from the list of trusted certificates");
		if (trusted) {
			*reason = X509_VALIDATE_UNKNOWN_CA;
			return -1;
		}
		wpa_printf(MSG_DEBUG, "X509: Certificate chain validation "
			   "disabled - ignore unknown CA issue");
	}

	wpa_printf(MSG_DEBUG, "X509: Certificate chain valid");

	return 0;
}
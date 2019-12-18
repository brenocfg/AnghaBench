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
typedef  int /*<<< orphan*/  HostnameValidationResult ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_data (int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MalformedCertificate ; 
 int /*<<< orphan*/  MatchFound ; 
 int /*<<< orphan*/  MatchNotFound ; 
 scalar_t__ has_nul (char*,int) ; 
 scalar_t__ memeq_ncase (char const*,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static HostnameValidationResult validate_name(const char *hostname, ASN1_STRING *certname_asn1) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && !defined(LIBRESSL_VERSION_NUMBER)
	char *certname_s = (char *) ASN1_STRING_get0_data(certname_asn1);
#else
	char *certname_s = (char *) ASN1_STRING_data(certname_asn1);
#endif
	int certname_len = ASN1_STRING_length(certname_asn1), hostname_len = strlen(hostname);

	// Make sure there isn't an embedded NUL character in the DNS name
	if (has_nul(certname_s, certname_len)) {
		return MalformedCertificate;
	}
	// remove last '.' from hostname
	if (hostname_len != 0 && hostname[hostname_len - 1] == '.')
		--hostname_len;
	// skip the first segment if wildcard
	if (certname_len > 2 && certname_s[0] == '*' && certname_s[1] == '.') {
		if (hostname_len != 0) {
			do {
				--hostname_len;
				if (*hostname++ == '.')
					break;
			} while (hostname_len != 0);
		}
		certname_s += 2;
		certname_len -= 2;
	}
	// Compare expected hostname with the DNS name
	if (certname_len != hostname_len) {
		return MatchNotFound;
	}
	return memeq_ncase(hostname, certname_s, hostname_len) ? MatchFound : MatchNotFound;
}
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
typedef  int /*<<< orphan*/  cert_str ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int HostnameValidationResult ;

/* Variables and functions */
#define  Error 132 
#define  MalformedCertificate 131 
#define  MatchFound 130 
#define  MatchNotFound 129 
#define  NoSANPresent 128 
 int /*<<< orphan*/  X509_NAME_oneline (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int X509_verify_cert (int /*<<< orphan*/ *) ; 
 scalar_t__ ignore_cert ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,...) ; 
 int validate_hostname (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cert_verify_callback(X509_STORE_CTX *x509_ctx, void *arg)
{
	char cert_str[256];
	const char *host = (const char *) arg;
	const char *res_str = "X509_verify_cert failed";
	HostnameValidationResult res = Error;

	/* This is the function that OpenSSL would call if we hadn't called
	 * SSL_CTX_set_cert_verify_callback().  Therefore, we are "wrapping"
	 * the default functionality, rather than replacing it. */
	int ok_so_far = 0;

	X509 *server_cert = NULL;

	if (ignore_cert) {
		return 1;
	}

	ok_so_far = X509_verify_cert(x509_ctx);

	server_cert = X509_STORE_CTX_get_current_cert(x509_ctx);

	if (ok_so_far) {
		res = validate_hostname(host, server_cert);

		switch (res) {
		case MatchFound:
			res_str = "MatchFound";
			break;
		case MatchNotFound:
			res_str = "MatchNotFound";
			break;
		case NoSANPresent:
			res_str = "NoSANPresent";
			break;
		case MalformedCertificate:
			res_str = "MalformedCertificate";
			break;
		case Error:
			res_str = "Error";
			break;
		default:
			res_str = "WTF!";
			break;
		}
	}

	X509_NAME_oneline(X509_get_subject_name (server_cert),
			  cert_str, sizeof (cert_str));

	if (res == MatchFound) {
		printf("https server '%s' has this certificate, "
		       "which looks good to me:\n%s\n",
		       host, cert_str);
		return 1;
	} else {
		printf("Got '%s' for hostname '%s' and certificate:\n%s\n",
		       res_str, host, cert_str);
		return 0;
	}
}
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
typedef  int /*<<< orphan*/  mdstr ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  EX_NOPERM ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int X509_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
tls_certificate_verify(SSL *ssl, const char *fingerprint)
{
	unsigned char md[EVP_MAX_MD_SIZE];
	char mdstr[sizeof("SHA256=") - 1 + EVP_MAX_MD_SIZE * 3];
	char *mdstrp;
	unsigned int i, mdsize;
	X509 *cert;

	if (fingerprint[0] == '\0') {
		pjdlog_debug(1, "No fingerprint verification requested.");
		return;
	}

	cert = SSL_get_peer_certificate(ssl);
	if (cert == NULL)
		pjdlog_exitx(EX_TEMPFAIL, "No peer certificate received.");

	if (X509_digest(cert, EVP_sha256(), md, &mdsize) != 1)
		pjdlog_exitx(EX_TEMPFAIL, "X509_digest() failed.");
	PJDLOG_ASSERT(mdsize <= EVP_MAX_MD_SIZE);

	X509_free(cert);

	(void)strlcpy(mdstr, "SHA256=", sizeof(mdstr));
	mdstrp = mdstr + strlen(mdstr);
	for (i = 0; i < mdsize; i++) {
		PJDLOG_VERIFY(mdstrp + 3 <= mdstr + sizeof(mdstr));
		(void)sprintf(mdstrp, "%02hhX:", md[i]);
		mdstrp += 3;
	}
	/* Clear last colon. */
	mdstrp[-1] = '\0';
	if (strcasecmp(mdstr, fingerprint) != 0) {
		pjdlog_exitx(EX_NOPERM,
		    "Finger print doesn't match. Received \"%s\", expected \"%s\"",
		    mdstr, fingerprint);
	}
}
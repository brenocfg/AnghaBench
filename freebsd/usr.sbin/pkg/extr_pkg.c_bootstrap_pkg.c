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

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  PACKAGESITE ; 
 int /*<<< orphan*/  SIGNATURE_TYPE ; 
 int /*<<< orphan*/  URL_SCHEME_PREFIX ; 
 char* _PATH_TMP ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ config_string (int /*<<< orphan*/ ,char const**) ; 
 int extract_pkg_static (int,char*,int) ; 
 int /*<<< orphan*/  fetchLastErrString ; 
 int fetch_to_fd (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int install_pkg_static (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int verify_pubsignature (int,int) ; 
 int verify_signature (int,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
bootstrap_pkg(bool force)
{
	int fd_pkg, fd_sig;
	int ret;
	char url[MAXPATHLEN];
	char tmppkg[MAXPATHLEN];
	char tmpsig[MAXPATHLEN];
	const char *packagesite;
	const char *signature_type;
	char pkgstatic[MAXPATHLEN];

	fd_sig = -1;
	ret = -1;

	if (config_string(PACKAGESITE, &packagesite) != 0) {
		warnx("No PACKAGESITE defined");
		return (-1);
	}

	if (config_string(SIGNATURE_TYPE, &signature_type) != 0) {
		warnx("Error looking up SIGNATURE_TYPE");
		return (-1);
	}

	printf("Bootstrapping pkg from %s, please wait...\n", packagesite);

	/* Support pkg+http:// for PACKAGESITE which is the new format
	   in 1.2 to avoid confusion on why http://pkg.FreeBSD.org has
	   no A record. */
	if (strncmp(URL_SCHEME_PREFIX, packagesite,
	    strlen(URL_SCHEME_PREFIX)) == 0)
		packagesite += strlen(URL_SCHEME_PREFIX);
	snprintf(url, MAXPATHLEN, "%s/Latest/pkg.txz", packagesite);

	snprintf(tmppkg, MAXPATHLEN, "%s/pkg.txz.XXXXXX",
	    getenv("TMPDIR") ? getenv("TMPDIR") : _PATH_TMP);

	if ((fd_pkg = fetch_to_fd(url, tmppkg)) == -1)
		goto fetchfail;

	if (signature_type != NULL &&
	    strcasecmp(signature_type, "NONE") != 0) {
		if (strcasecmp(signature_type, "FINGERPRINTS") == 0) {

			snprintf(tmpsig, MAXPATHLEN, "%s/pkg.txz.sig.XXXXXX",
			    getenv("TMPDIR") ? getenv("TMPDIR") : _PATH_TMP);
			snprintf(url, MAXPATHLEN, "%s/Latest/pkg.txz.sig",
			    packagesite);

			if ((fd_sig = fetch_to_fd(url, tmpsig)) == -1) {
				fprintf(stderr, "Signature for pkg not "
				    "available.\n");
				goto fetchfail;
			}

			if (verify_signature(fd_pkg, fd_sig) == false)
				goto cleanup;
		} else if (strcasecmp(signature_type, "PUBKEY") == 0) {

			snprintf(tmpsig, MAXPATHLEN,
			    "%s/pkg.txz.pubkeysig.XXXXXX",
			    getenv("TMPDIR") ? getenv("TMPDIR") : _PATH_TMP);
			snprintf(url, MAXPATHLEN, "%s/Latest/pkg.txz.pubkeysig",
			    packagesite);

			if ((fd_sig = fetch_to_fd(url, tmpsig)) == -1) {
				fprintf(stderr, "Signature for pkg not "
				    "available.\n");
				goto fetchfail;
			}

			if (verify_pubsignature(fd_pkg, fd_sig) == false)
				goto cleanup;
		} else {
			warnx("Signature type %s is not supported for "
			    "bootstrapping.", signature_type);
			goto cleanup;
		}
	}

	if ((ret = extract_pkg_static(fd_pkg, pkgstatic, MAXPATHLEN)) == 0)
		ret = install_pkg_static(pkgstatic, tmppkg, force);

	goto cleanup;

fetchfail:
	warnx("Error fetching %s: %s", url, fetchLastErrString);
	fprintf(stderr, "A pre-built version of pkg could not be found for "
	    "your system.\n");
	fprintf(stderr, "Consider changing PACKAGESITE or installing it from "
	    "ports: 'ports-mgmt/pkg'.\n");

cleanup:
	if (fd_sig != -1) {
		close(fd_sig);
		unlink(tmpsig);
	}

	if (fd_pkg != -1) {
		close(fd_pkg);
		unlink(tmppkg);
	}

	return (ret);
}
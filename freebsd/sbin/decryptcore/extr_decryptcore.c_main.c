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
typedef  int /*<<< orphan*/  keyfile ;
typedef  int /*<<< orphan*/  encryptedcore ;
typedef  int /*<<< orphan*/  core ;

/* Variables and functions */
 char* DECRYPTCORE_CRASHDIR ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PJDLOG_MODE_STD ; 
 int /*<<< orphan*/  PJDLOG_MODE_SYSLOG ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 int /*<<< orphan*/  decrypt (int,char const*,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ isdigit (int) ; 
 int open (char*,int,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pjdlog_debug_set (int) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pjdlog_exitx (int,char*) ; 
 int /*<<< orphan*/  pjdlog_fini () ; 
 int /*<<< orphan*/  pjdlog_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_mode_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*) ; 
 scalar_t__ snprintf (char*,int,char*,char const*,char const*) ; 
 int strlcpy (char*,char*,int) ; 
 size_t strnlen (char const*,int) ; 
 int unlink (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	char core[PATH_MAX], encryptedcore[PATH_MAX], keyfile[PATH_MAX];
	const char *crashdir, *dumpnr, *privatekey;
	int ch, debug, error, ofd;
	size_t ii;
	bool force, usesyslog;

	error = 1;

	pjdlog_init(PJDLOG_MODE_STD);
	pjdlog_prefix_set("(decryptcore) ");

	debug = 0;
	*core = '\0';
	crashdir = NULL;
	dumpnr = NULL;
	*encryptedcore = '\0';
	force = false;
	*keyfile = '\0';
	privatekey = NULL;
	usesyslog = false;
	while ((ch = getopt(argc, argv, "Lc:d:e:fk:n:p:v")) != -1) {
		switch (ch) {
		case 'L':
			usesyslog = true;
			break;
		case 'c':
			if (strlcpy(core, optarg, sizeof(core)) >= sizeof(core))
				pjdlog_exitx(1, "Core file path is too long.");
			break;
		case 'd':
			crashdir = optarg;
			break;
		case 'e':
			if (strlcpy(encryptedcore, optarg,
			    sizeof(encryptedcore)) >= sizeof(encryptedcore)) {
				pjdlog_exitx(1, "Encrypted core file path is too long.");
			}
			break;
		case 'f':
			force = true;
			break;
		case 'k':
			if (strlcpy(keyfile, optarg, sizeof(keyfile)) >=
			    sizeof(keyfile)) {
				pjdlog_exitx(1, "Key file path is too long.");
			}
			break;
		case 'n':
			dumpnr = optarg;
			break;
		case 'p':
			privatekey = optarg;
			break;
		case 'v':
			debug++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

	/* Verify mutually exclusive options. */
	if ((crashdir != NULL || dumpnr != NULL) &&
	    (*keyfile != '\0' || *encryptedcore != '\0' || *core != '\0')) {
		usage();
	}

	/*
	 * Set key, encryptedcore and core file names using crashdir and dumpnr.
	 */
	if (dumpnr != NULL) {
		for (ii = 0; ii < strnlen(dumpnr, PATH_MAX); ii++) {
			if (isdigit((int)dumpnr[ii]) == 0)
				usage();
		}

		if (crashdir == NULL)
			crashdir = DECRYPTCORE_CRASHDIR;
		PJDLOG_VERIFY(snprintf(keyfile, sizeof(keyfile),
		    "%s/key.%s", crashdir, dumpnr) > 0);
		PJDLOG_VERIFY(snprintf(core, sizeof(core),
		    "%s/vmcore.%s", crashdir, dumpnr) > 0);
		PJDLOG_VERIFY(snprintf(encryptedcore, sizeof(encryptedcore),
		    "%s/vmcore_encrypted.%s", crashdir, dumpnr) > 0);
	}

	if (privatekey == NULL || *keyfile == '\0' || *encryptedcore == '\0' ||
	    *core == '\0') {
		usage();
	}

	if (usesyslog)
		pjdlog_mode_set(PJDLOG_MODE_SYSLOG);
	pjdlog_debug_set(debug);

	if (force && unlink(core) == -1 && errno != ENOENT) {
		pjdlog_errno(LOG_ERR, "Unable to remove old core");
		goto out;
	}
	ofd = open(core, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (ofd == -1) {
		pjdlog_errno(LOG_ERR, "Unable to open %s", core);
		goto out;
	}

	if (!decrypt(ofd, privatekey, keyfile, encryptedcore)) {
		if (unlink(core) == -1 && errno != ENOENT)
			pjdlog_errno(LOG_ERR, "Unable to remove core");
		goto out;
	}

	error = 0;
out:
	pjdlog_fini();
	exit(error);
}
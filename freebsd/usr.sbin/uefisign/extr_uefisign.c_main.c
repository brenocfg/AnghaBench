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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_LOAD_CONFIG ; 
 int OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * checked_fopen (char const*,char*) ; 
 char* checked_strdup (int /*<<< orphan*/ ) ; 
 int child (char const*,char const*,int,int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fork () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 int wait_for_child (scalar_t__) ; 

int
main(int argc, char **argv)
{
	int ch, error;
	bool Vflag = false, vflag = false;
	const char *certpath = NULL, *keypath = NULL, *outpath = NULL, *inpath = NULL;
	FILE *certfp = NULL, *keyfp = NULL;
	X509 *cert = NULL;
	EVP_PKEY *key = NULL;
	pid_t pid;
	int pipefds[2];

	while ((ch = getopt(argc, argv, "Vc:k:o:v")) != -1) {
		switch (ch) {
		case 'V':
			Vflag = true;
			break;
		case 'c':
			certpath = checked_strdup(optarg);
			break;
		case 'k':
			keypath = checked_strdup(optarg);
			break;
		case 'o':
			outpath = checked_strdup(optarg);
			break;
		case 'v':
			vflag = true;
			break;
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;
	if (argc != 1)
		usage();

	if (Vflag) {
		if (certpath != NULL)
			errx(1, "-V and -c are mutually exclusive");
		if (keypath != NULL)
			errx(1, "-V and -k are mutually exclusive");
		if (outpath != NULL)
			errx(1, "-V and -o are mutually exclusive");
	} else {
		if (certpath == NULL)
			errx(1, "-c option is mandatory");
		if (keypath == NULL)
			errx(1, "-k option is mandatory");
		if (outpath == NULL)
			errx(1, "-o option is mandatory");
	}

	inpath = argv[0];

	OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG |
	    OPENSSL_INIT_LOAD_CRYPTO_STRINGS |
	    OPENSSL_INIT_ADD_ALL_CIPHERS | OPENSSL_INIT_ADD_ALL_DIGESTS, NULL);

	error = pipe(pipefds);
	if (error != 0)
		err(1, "pipe");

	pid = fork();
	if (pid < 0)
		err(1, "fork");

	if (pid == 0)
		return (child(inpath, outpath, pipefds[1], Vflag, vflag));

	if (!Vflag) {
		certfp = checked_fopen(certpath, "r");
		cert = PEM_read_X509(certfp, NULL, NULL, NULL);
		if (cert == NULL) {
			ERR_print_errors_fp(stderr);
			errx(1, "failed to load certificate from %s", certpath);
		}

		keyfp = checked_fopen(keypath, "r");
		key = PEM_read_PrivateKey(keyfp, NULL, NULL, NULL);
		if (key == NULL) {
			ERR_print_errors_fp(stderr);
			errx(1, "failed to load private key from %s", keypath);
		}

		sign(cert, key, pipefds[0]);
	}

	return (wait_for_child(pid));
}
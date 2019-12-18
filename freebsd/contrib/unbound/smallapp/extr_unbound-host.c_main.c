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
struct ub_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_load_SSL_strings () ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 scalar_t__ NSS_NoDB_Init (char*) ; 
 int OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 char* ROOT_ANCHOR_FILE ; 
 scalar_t__ SECSuccess ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  check_ub_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  lookup (struct ub_ctx*,char*,char*,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  ub_ctx_add_ta (struct ub_ctx*,char*) ; 
 int /*<<< orphan*/  ub_ctx_add_ta_file (struct ub_ctx*,char*) ; 
 int /*<<< orphan*/  ub_ctx_config (struct ub_ctx*,char*) ; 
 struct ub_ctx* ub_ctx_create () ; 
 int /*<<< orphan*/  ub_ctx_debuglevel (struct ub_ctx*,int) ; 
 scalar_t__ ub_ctx_get_option (struct ub_ctx*,char*,char**) ; 
 int /*<<< orphan*/  ub_ctx_resolvconf (struct ub_ctx*,char*) ; 
 int /*<<< orphan*/  ub_ctx_set_option (struct ub_ctx*,char*,char*) ; 
 int /*<<< orphan*/  ub_ctx_trustedkeys (struct ub_ctx*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verb ; 

int main(int argc, char* argv[])
{
	int c;
	char* qclass = NULL;
	char* qtype = NULL;
	struct ub_ctx* ctx = NULL;
	int debuglevel = 0;
	
	ctx = ub_ctx_create();
	if(!ctx) {
		fprintf(stderr, "error: out of memory\n");
		exit(1);
	}
	/* no need to fetch additional targets, we only do few lookups */
	check_ub_res(ub_ctx_set_option(ctx, "target-fetch-policy:", "0 0 0 0 0"));

	/* parse the options */
	while( (c=getopt(argc, argv, "46DF:c:df:hrt:vy:C:")) != -1) {
		switch(c) {
		case '4':
			check_ub_res(ub_ctx_set_option(ctx, "do-ip6:", "no"));
			break;
		case '6':
			check_ub_res(ub_ctx_set_option(ctx, "do-ip4:", "no"));
			break;
		case 'c':
			qclass = optarg;
			break;
		case 'C':
			check_ub_res(ub_ctx_config(ctx, optarg));
			break;
		case 'D':
			check_ub_res(ub_ctx_add_ta_file(ctx, ROOT_ANCHOR_FILE));
			break;
		case 'd':
			debuglevel++;
			if(debuglevel < 2) 
				debuglevel = 2; /* at least VERB_DETAIL */
			break;
		case 'r':
			check_ub_res(ub_ctx_resolvconf(ctx, "/etc/resolv.conf"));
			break;
		case 't':
			qtype = optarg;
			break;
		case 'v':
			verb++;
			break;
		case 'y':
			check_ub_res(ub_ctx_add_ta(ctx, optarg));
			break;
		case 'f':
			check_ub_res(ub_ctx_add_ta_file(ctx, optarg));
			break;
		case 'F':
			check_ub_res(ub_ctx_trustedkeys(ctx, optarg));
			break;
		case '?':
		case 'h':
		default:
			usage();
		}
	}
	if(debuglevel != 0) /* set after possible -C options */
		check_ub_res(ub_ctx_debuglevel(ctx, debuglevel));
	if(ub_ctx_get_option(ctx, "use-syslog", &optarg) == 0) {
		if(strcmp(optarg, "yes") == 0) /* disable use-syslog */
			check_ub_res(ub_ctx_set_option(ctx, 
				"use-syslog:", "no"));
		free(optarg);
	}
	argc -= optind;
	argv += optind;
	if(argc != 1)
		usage();

#ifdef HAVE_SSL
#ifdef HAVE_ERR_LOAD_CRYPTO_STRINGS
	ERR_load_crypto_strings();
#endif
#if OPENSSL_VERSION_NUMBER < 0x10100000 || !defined(HAVE_OPENSSL_INIT_SSL)
	ERR_load_SSL_strings();
#endif
#if OPENSSL_VERSION_NUMBER < 0x10100000 || !defined(HAVE_OPENSSL_INIT_CRYPTO)
	OpenSSL_add_all_algorithms();
#else
	OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_CIPHERS
		| OPENSSL_INIT_ADD_ALL_DIGESTS
		| OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
#endif
#if OPENSSL_VERSION_NUMBER < 0x10100000 || !defined(HAVE_OPENSSL_INIT_SSL)
	(void)SSL_library_init();
#else
	(void)OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL);
#endif
#endif /* HAVE_SSL */
#ifdef HAVE_NSS
        if(NSS_NoDB_Init(".") != SECSuccess) {
		fprintf(stderr, "could not init NSS\n");
		return 1;
	}
#endif
	lookup(ctx, argv[0], qtype, qclass);
	return 0;
}
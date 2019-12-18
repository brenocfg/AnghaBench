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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 char* CONFIGFILE ; 
 int /*<<< orphan*/  ERR_load_SSL_strings () ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  RAND_seed (unsigned char*,int) ; 
 int /*<<< orphan*/  RAND_status () ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checklock_start () ; 
 int /*<<< orphan*/  checklock_stop () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ execlp (char*,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  fatal_exit (char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getpid () ; 
 int go (char const*,char*,int,int,char**) ; 
 int /*<<< orphan*/  log_ident_set (char*) ; 
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned int*,int) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_stats_shm (char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 char* w_lookup_reg_str (char*,char*) ; 
 int /*<<< orphan*/  wsa_strerror (int) ; 

int main(int argc, char* argv[])
{
	int c, ret;
	int quiet = 0;
	const char* cfgfile = CONFIGFILE;
	char* svr = NULL;
#ifdef USE_WINSOCK
	int r;
	WSADATA wsa_data;
#endif
#ifdef USE_THREAD_DEBUG
	/* stop the file output from unbound-control, overwrites the servers */
	extern int check_locking_order;
	check_locking_order = 0;
#endif /* USE_THREAD_DEBUG */
	log_ident_set("unbound-control");
	log_init(NULL, 0, NULL);
	checklock_start();
#ifdef USE_WINSOCK
	/* use registry config file in preference to compiletime location */
	if(!(cfgfile=w_lookup_reg_str("Software\\Unbound", "ConfigFile")))
		cfgfile = CONFIGFILE;
#endif
	/* parse the options */
	while( (c=getopt(argc, argv, "c:s:qh")) != -1) {
		switch(c) {
		case 'c':
			cfgfile = optarg;
			break;
		case 's':
			svr = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		case '?':
		case 'h':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if(argc == 0)
		usage();
	if(argc >= 1 && strcmp(argv[0], "start")==0) {
		if(execlp("unbound", "unbound", "-c", cfgfile, 
			(char*)NULL) < 0) {
			fatal_exit("could not exec unbound: %s",
				strerror(errno));
		}
	}
	if(argc >= 1 && strcmp(argv[0], "stats_shm")==0) {
		print_stats_shm(cfgfile);
		return 0;
	}

#ifdef USE_WINSOCK
	if((r = WSAStartup(MAKEWORD(2,2), &wsa_data)) != 0)
		fatal_exit("WSAStartup failed: %s", wsa_strerror(r));
#endif

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

	if(!RAND_status()) {
		/* try to seed it */
		unsigned char buf[256];
		unsigned int seed=(unsigned)time(NULL) ^ (unsigned)getpid();
		unsigned int v = seed;
		size_t i;
		for(i=0; i<256/sizeof(v); i++) {
			memmove(buf+i*sizeof(v), &v, sizeof(v));
			v = v*seed + (unsigned int)i;
		}
		RAND_seed(buf, 256);
		log_warn("no entropy, seeding openssl PRNG with time\n");
	}

	ret = go(cfgfile, svr, quiet, argc, argv);

#ifdef USE_WINSOCK
	WSACleanup();
#endif
	checklock_stop();
	return ret;
}
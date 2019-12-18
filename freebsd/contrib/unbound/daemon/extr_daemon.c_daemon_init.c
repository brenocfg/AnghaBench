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
struct module_env {struct module_env* env; int /*<<< orphan*/  tcl; int /*<<< orphan*/  acl; int /*<<< orphan*/  auth_zones; int /*<<< orphan*/  time_boot; int /*<<< orphan*/  time_last_stat; int /*<<< orphan*/  superalloc; int /*<<< orphan*/  mods; scalar_t__ need_to_exit; } ;
struct daemon {struct daemon* env; int /*<<< orphan*/  tcl; int /*<<< orphan*/  acl; int /*<<< orphan*/  auth_zones; int /*<<< orphan*/  time_boot; int /*<<< orphan*/  time_last_stat; int /*<<< orphan*/  superalloc; int /*<<< orphan*/  mods; scalar_t__ need_to_exit; } ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_load_SSL_strings () ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ NSS_NoDB_Init (int /*<<< orphan*/ *) ; 
 int OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 scalar_t__ SECSuccess ; 
 scalar_t__ SSL_COMP_get_compression_methods () ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_list_create () ; 
 int /*<<< orphan*/  acl_list_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_zones_create () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  checklock_start () ; 
 void* comp_meth ; 
 int /*<<< orphan*/  edns_known_options_delete (struct module_env*) ; 
 int /*<<< orphan*/  edns_known_options_init (struct module_env*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 int /*<<< orphan*/  free (struct module_env*) ; 
 scalar_t__ getpid () ; 
 scalar_t__ gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handling_record () ; 
 int /*<<< orphan*/  sldns_key_EVP_load_gost_id () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcl_list_create () ; 
 int /*<<< orphan*/  tcl_list_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  ub_openssl_lock_init () ; 
 int /*<<< orphan*/  ub_systemseed (unsigned int) ; 
 int /*<<< orphan*/  wsa_strerror (int) ; 

struct daemon* 
daemon_init(void)
{
	struct daemon* daemon = (struct daemon*)calloc(1, 
		sizeof(struct daemon));
#ifdef USE_WINSOCK
	int r;
	WSADATA wsa_data;
#endif
	if(!daemon)
		return NULL;
#ifdef USE_WINSOCK
	r = WSAStartup(MAKEWORD(2,2), &wsa_data);
	if(r != 0) {
		fatal_exit("could not init winsock. WSAStartup: %s",
			wsa_strerror(r));
	}
#endif /* USE_WINSOCK */
	signal_handling_record();
	checklock_start();
#ifdef HAVE_SSL
#  ifdef HAVE_ERR_LOAD_CRYPTO_STRINGS
	ERR_load_crypto_strings();
#  endif
#if OPENSSL_VERSION_NUMBER < 0x10100000 || !defined(HAVE_OPENSSL_INIT_SSL)
	ERR_load_SSL_strings();
#endif
#  ifdef USE_GOST
	(void)sldns_key_EVP_load_gost_id();
#  endif
#  if OPENSSL_VERSION_NUMBER < 0x10100000 || !defined(HAVE_OPENSSL_INIT_CRYPTO)
	OpenSSL_add_all_algorithms();
#  else
	OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_CIPHERS
		| OPENSSL_INIT_ADD_ALL_DIGESTS
		| OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
#  endif
#  if HAVE_DECL_SSL_COMP_GET_COMPRESSION_METHODS
	/* grab the COMP method ptr because openssl leaks it */
	comp_meth = (void*)SSL_COMP_get_compression_methods();
#  endif
#  if OPENSSL_VERSION_NUMBER < 0x10100000 || !defined(HAVE_OPENSSL_INIT_SSL)
	(void)SSL_library_init();
#  else
	(void)OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL);
#  endif
#  if defined(HAVE_SSL) && defined(OPENSSL_THREADS) && !defined(THREADS_DISABLED)
	if(!ub_openssl_lock_init())
		fatal_exit("could not init openssl locks");
#  endif
#elif defined(HAVE_NSS)
	if(NSS_NoDB_Init(NULL) != SECSuccess)
		fatal_exit("could not init NSS");
#endif /* HAVE_SSL or HAVE_NSS */
#ifdef HAVE_TZSET
	/* init timezone info while we are not chrooted yet */
	tzset();
#endif
	/* open /dev/random if needed */
	ub_systemseed((unsigned)time(NULL)^(unsigned)getpid()^0xe67);
	daemon->need_to_exit = 0;
	modstack_init(&daemon->mods);
	if(!(daemon->env = (struct module_env*)calloc(1, 
		sizeof(*daemon->env)))) {
		free(daemon);
		return NULL;
	}
	/* init edns_known_options */
	if(!edns_known_options_init(daemon->env)) {
		free(daemon->env);
		free(daemon);
		return NULL;
	}
	alloc_init(&daemon->superalloc, NULL, 0);
	daemon->acl = acl_list_create();
	if(!daemon->acl) {
		edns_known_options_delete(daemon->env);
		free(daemon->env);
		free(daemon);
		return NULL;
	}
	daemon->tcl = tcl_list_create();
	if(!daemon->tcl) {
		acl_list_delete(daemon->acl);
		edns_known_options_delete(daemon->env);
		free(daemon->env);
		free(daemon);
		return NULL;
	}
	if(gettimeofday(&daemon->time_boot, NULL) < 0)
		log_err("gettimeofday: %s", strerror(errno));
	daemon->time_last_stat = daemon->time_boot;
	if((daemon->env->auth_zones = auth_zones_create()) == 0) {
		acl_list_delete(daemon->acl);
		tcl_list_delete(daemon->tcl);
		edns_known_options_delete(daemon->env);
		free(daemon->env);
		free(daemon);
		return NULL;
	}
	return daemon;	
}
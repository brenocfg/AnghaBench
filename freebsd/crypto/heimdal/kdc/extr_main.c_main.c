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
struct sigaction {void* sa_handler; int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ KRB5_CONFIG_BADFORMAT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGXCPU ; 
 void* SIG_IGN ; 
 int /*<<< orphan*/  bonjour_announce (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * configure (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ detach_from_console ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  hdb_kt_ops ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void*) ; 
 void* sigterm ; 
 int /*<<< orphan*/  switch_environment () ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_kdc_configuration *config;

    setprogname(argv[0]);

    ret = krb5_init_context(&context);
    if (ret == KRB5_CONFIG_BADFORMAT)
	errx (1, "krb5_init_context failed to parse configuration file");
    else if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    ret = krb5_kt_register(context, &hdb_kt_ops);
    if (ret)
	errx (1, "krb5_kt_register(HDB) failed: %d", ret);

    config = configure(context, argc, argv);

#ifdef HAVE_SIGACTION
    {
	struct sigaction sa;

	sa.sa_flags = 0;
	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
#ifdef SIGXCPU
	sigaction(SIGXCPU, &sa, NULL);
#endif

	sa.sa_handler = SIG_IGN;
#ifdef SIGPIPE
	sigaction(SIGPIPE, &sa, NULL);
#endif
    }
#else
    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);
#ifdef SIGXCPU
    signal(SIGXCPU, sigterm);
#endif
#ifdef SIGPIPE
    signal(SIGPIPE, SIG_IGN);
#endif
#endif
#ifdef SUPPORT_DETACH
    if (detach_from_console)
	daemon(0, 0);
#endif
#ifdef __APPLE__
    bonjour_announce(context, config);
#endif
    pidfile(NULL);

    switch_environment();

    loop(context, config);
    krb5_free_context(context);
    return 0;
}
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
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  heim_sipc ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 void* SIG_IGN ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ detach_from_console ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  heim_ipc_main () ; 
 int /*<<< orphan*/  heim_sipc_launchd_mach_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_sipc_service_unix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_configure (int,char**) ; 
 int /*<<< orphan*/  kcm_context ; 
 int /*<<< orphan*/  kcm_service ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ launchd_flag ; 
 int /*<<< orphan*/  pidfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_name ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void*) ; 
 void* sigterm ; 
 void* sigusr1 ; 
 void* sigusr2 ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    setprogname(argv[0]);

    ret = krb5_init_context(&kcm_context);
    if (ret) {
	errx (1, "krb5_init_context failed: %d", ret);
	return ret;
    }

    kcm_configure(argc, argv);

#ifdef HAVE_SIGACTION
    {
	struct sigaction sa;

	sa.sa_flags = 0;
	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	sa.sa_handler = sigusr1;
	sigaction(SIGUSR1, &sa, NULL);

	sa.sa_handler = sigusr2;
	sigaction(SIGUSR2, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);
    }
#else
    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);
    signal(SIGUSR1, sigusr1);
    signal(SIGUSR2, sigusr2);
    signal(SIGPIPE, SIG_IGN);
#endif
#ifdef SUPPORT_DETACH
    if (detach_from_console)
	daemon(0, 0);
#endif
    pidfile(NULL);

    if (launchd_flag) {
	heim_sipc mach;
	heim_sipc_launchd_mach_init(service_name, kcm_service, NULL, &mach);
    } else {
	heim_sipc un;
	heim_sipc_service_unix(service_name, kcm_service, NULL, &un);
    }

    heim_ipc_main();

    krb5_free_context(kcm_context);
    return 0;
}
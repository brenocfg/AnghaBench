#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rlim_t ;
struct TYPE_7__ {int /*<<< orphan*/  rlimit; } ;
typedef  TYPE_2__ config_tree ;
struct TYPE_6__ {int i; } ;
struct TYPE_8__ {int attr; TYPE_1__ value; struct TYPE_8__* link; } ;
typedef  TYPE_3__ attr_val ;

/* Variables and functions */
 int /*<<< orphan*/  HAVE_OPT (int /*<<< orphan*/ ) ; 
 TYPE_3__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 int /*<<< orphan*/  SAVECONFIGQUIT ; 
#define  T_Filenum 130 
#define  T_Memlock 129 
#define  T_Stacksize 128 
 int cur_memlock ; 
 int /*<<< orphan*/  fatal_error (char*,int) ; 
 int mlockall (int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int munlockall () ; 
 int /*<<< orphan*/  ntp_rlimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
config_rlimit(
	config_tree *ptree
	)
{
	attr_val *	rlimit_av;

	rlimit_av = HEAD_PFIFO(ptree->rlimit);
	for (; rlimit_av != NULL; rlimit_av = rlimit_av->link) {
		switch (rlimit_av->attr) {

		default:
			fatal_error("config-rlimit: value-token=%d", rlimit_av->attr);

		case T_Memlock:
			/* What if we HAVE_OPT(SAVECONFIGQUIT) ? */
			if (HAVE_OPT( SAVECONFIGQUIT )) {
				break;
			}
			if (rlimit_av->value.i == -1) {
# if defined(HAVE_MLOCKALL)
				if (cur_memlock != 0) {
					if (-1 == munlockall()) {
						msyslog(LOG_ERR, "munlockall() failed: %m");
					}
				}
				cur_memlock = 0;
# endif /* HAVE_MLOCKALL */
			} else if (rlimit_av->value.i >= 0) {
#if defined(RLIMIT_MEMLOCK)
# if defined(HAVE_MLOCKALL)
				if (cur_memlock != 1) {
					if (-1 == mlockall(MCL_CURRENT|MCL_FUTURE)) {
						msyslog(LOG_ERR, "mlockall() failed: %m");
					}
				}
# endif /* HAVE_MLOCKALL */
				ntp_rlimit(RLIMIT_MEMLOCK,
					   (rlim_t)(rlimit_av->value.i * 1024 * 1024),
					   1024 * 1024,
					   "MB");
				cur_memlock = 1;
#else
				/* STDERR as well would be fine... */
				msyslog(LOG_WARNING, "'rlimit memlock' specified but is not available on this system.");
#endif /* RLIMIT_MEMLOCK */
			} else {
				msyslog(LOG_WARNING, "'rlimit memlock' value of %d is unexpected!", rlimit_av->value.i);
			}
			break;

		case T_Stacksize:
#if defined(RLIMIT_STACK)
			ntp_rlimit(RLIMIT_STACK,
				   (rlim_t)(rlimit_av->value.i * 4096),
				   4096,
				   "4k");
#else
			/* STDERR as well would be fine... */
			msyslog(LOG_WARNING, "'rlimit stacksize' specified but is not available on this system.");
#endif /* RLIMIT_STACK */
			break;

		case T_Filenum:
#if defined(RLIMIT_NOFILE)
			ntp_rlimit(RLIMIT_NOFILE,
				  (rlim_t)(rlimit_av->value.i),
				  1,
				  "");
#else
			/* STDERR as well would be fine... */
			msyslog(LOG_WARNING, "'rlimit filenum' specified but is not available on this system.");
#endif /* RLIMIT_NOFILE */
			break;

		}
	}
}
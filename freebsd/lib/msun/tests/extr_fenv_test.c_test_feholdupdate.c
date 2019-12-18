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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  int /*<<< orphan*/  fenv_t ;

/* Variables and functions */
 int ALL_STD_EXCEPT ; 
 int FE_ALL_EXCEPT ; 
 int FE_DIVBYZERO ; 
 int /*<<< orphan*/  FE_DOWNWARD ; 
 int FE_INEXACT ; 
 int FE_INVALID ; 
 int /*<<< orphan*/  FE_UPWARD ; 
 unsigned int NEXCEPTS ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int feenableexcept (int) ; 
 int /*<<< orphan*/  fegetround () ; 
 int /*<<< orphan*/  feholdexcept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fesetround (int /*<<< orphan*/ ) ; 
 scalar_t__ fetestexcept (int) ; 
 int /*<<< orphan*/  feupdateenv (int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  raiseexcept (int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int* std_excepts ; 
 int /*<<< orphan*/  trap_handler ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void
test_feholdupdate(void)
{
	fenv_t env;

	struct sigaction act;
	int except, pass, status, raise;
	unsigned i;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = trap_handler;
	for (pass = 0; pass < 2; pass++) {
		for (i = 0; i < NEXCEPTS; i++) {
			except = std_excepts[i];
			/* over/underflow may also raise inexact */
			if (except == FE_INEXACT)
				raise = FE_DIVBYZERO | FE_INVALID;
			else
				raise = ALL_STD_EXCEPT ^ except;

			/*
			 * We need to fork a child process because
			 * there isn't a portable way to recover from
			 * a floating-point exception.
			 */
			switch(fork()) {
			case 0:		/* child */
				/*
				 * We don't want to cause a fatal exception in
				 * the child until the second pass, so we can
				 * check other properties of feupdateenv().
				 */
				if (pass == 1)
					assert((feenableexcept(except) &
						   ALL_STD_EXCEPT) == 0);
				raiseexcept(raise);
				assert(fesetround(FE_DOWNWARD) == 0);
				assert(feholdexcept(&env) == 0);
				assert(fetestexcept(FE_ALL_EXCEPT) == 0);
				raiseexcept(except);
				assert(fesetround(FE_UPWARD) == 0);

				if (pass == 1)
					assert(sigaction(SIGFPE, &act, NULL) ==
					    0);
				assert(feupdateenv(&env) == 0);
				assert(fegetround() == FE_DOWNWARD);
				assert(fetestexcept(ALL_STD_EXCEPT) ==
				    (except | raise));

				assert(pass == 0);
				_exit(0);
			default:	/* parent */
				assert(wait(&status) > 0);
				/*
				 * Avoid assert() here so that it's possible
				 * to examine a failed child's core dump.
				 */
				if (!WIFEXITED(status))
					errx(1, "child aborted\n");
				assert(WEXITSTATUS(status) == 0);
				break;
			case -1:	/* error */
				assert(0);
			}
		}
	}
	assert(fetestexcept(FE_ALL_EXCEPT) == 0);
}
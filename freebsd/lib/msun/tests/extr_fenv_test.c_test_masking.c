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

/* Variables and functions */
 int ALL_STD_EXCEPT ; 
 int FE_ALL_EXCEPT ; 
 int FE_DIVBYZERO ; 
 int FE_INEXACT ; 
 int FE_INVALID ; 
 int FE_OVERFLOW ; 
 int FE_UNDERFLOW ; 
 unsigned int NEXCEPTS ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int fedisableexcept (int) ; 
 int feenableexcept (int) ; 
 int fegetexcept () ; 
 int /*<<< orphan*/  feraiseexcept (int) ; 
 scalar_t__ fetestexcept (int) ; 
 int fork () ; 
 int /*<<< orphan*/  raiseexcept (int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int* std_excepts ; 
 int /*<<< orphan*/  trap_handler ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void
test_masking(void)
{
	struct sigaction act;
	int except, pass, raise, status;
	unsigned i;

	assert((fegetexcept() & ALL_STD_EXCEPT) == 0);
	assert((feenableexcept(FE_INVALID|FE_OVERFLOW) & ALL_STD_EXCEPT) == 0);
	assert((feenableexcept(FE_UNDERFLOW) & ALL_STD_EXCEPT) ==
	    (FE_INVALID | FE_OVERFLOW));
	assert((fedisableexcept(FE_OVERFLOW) & ALL_STD_EXCEPT) ==
	    (FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW));
	assert((fegetexcept() & ALL_STD_EXCEPT) == (FE_INVALID | FE_UNDERFLOW));
	assert((fedisableexcept(FE_ALL_EXCEPT) & ALL_STD_EXCEPT) ==
	    (FE_INVALID | FE_UNDERFLOW));
	assert((fegetexcept() & ALL_STD_EXCEPT) == 0);

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
				assert((fegetexcept() & ALL_STD_EXCEPT) == 0);
				assert((feenableexcept(except)
					   & ALL_STD_EXCEPT) == 0);
				assert(fegetexcept() == except);
				raiseexcept(raise);
				assert(feraiseexcept(raise) == 0);
				assert(fetestexcept(ALL_STD_EXCEPT) == raise);

				assert(sigaction(SIGFPE, &act, NULL) == 0);
				switch (pass) {
				case 0:
					raiseexcept(except);
				case 1:
					feraiseexcept(except);
				default:
					assert(0);
				}
				assert(0);
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
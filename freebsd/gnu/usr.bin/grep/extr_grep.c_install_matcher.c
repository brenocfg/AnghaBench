#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rlimit {long rlim_max; long rlim_cur; } ;
struct TYPE_2__ {int /*<<< orphan*/  execute; scalar_t__ compile; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_STACK ; 
 scalar_t__ compile ; 
 int /*<<< orphan*/  execute ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 TYPE_1__* matchers ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
install_matcher (char const *name)
{
  int i;
#if defined(HAVE_SETRLIMIT)
  struct rlimit rlim;
#endif

  for (i = 0; matchers[i].compile; i++)
    if (strcmp (name, matchers[i].name) == 0)
      {
	compile = matchers[i].compile;
	execute = matchers[i].execute;
#if defined(HAVE_SETRLIMIT) && defined(RLIMIT_STACK)
	/* I think every platform needs to do this, so that regex.c
	   doesn't oveflow the stack.  The default value of
	   `re_max_failures' is too large for some platforms: it needs
	   more than 3MB-large stack.

	   The test for HAVE_SETRLIMIT should go into `configure'.  */
	if (!getrlimit (RLIMIT_STACK, &rlim))
	  {
	    long newlim;
	    extern long int re_max_failures; /* from regex.c */

	    /* Approximate the amount regex.c needs, plus some more.  */
	    newlim = re_max_failures * 2 * 20 * sizeof (char *);
	    if (newlim > rlim.rlim_max)
	      {
		newlim = rlim.rlim_max;
		re_max_failures = newlim / (2 * 20 * sizeof (char *));
	      }
	    if (rlim.rlim_cur < newlim)
	      {
		rlim.rlim_cur = newlim;
		setrlimit (RLIMIT_STACK, &rlim);
	      }
	  }
#endif
	return 1;
      }
  return 0;
}
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
struct env_lst {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  TELOPT_NEW_ENVIRON ; 
 int /*<<< orphan*/  TELOPT_OLD_ENVIRON ; 
 struct env_lst* env_find (unsigned char*) ; 
 int /*<<< orphan*/  env_opt_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_opt_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_opt_start_info () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned char*) ; 
 scalar_t__ my_state_is_wont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
env_send(unsigned char *var)
{
	struct env_lst *ep;

	if (my_state_is_wont(TELOPT_NEW_ENVIRON)
#ifdef	OLD_ENVIRON
	    && my_state_is_wont(TELOPT_OLD_ENVIRON)
#endif
		) {
		fprintf(stderr,
		    "Cannot send '%s': Telnet ENVIRON option not enabled\n",
									var);
		return;
	}
	ep = env_find(var);
	if (ep == 0) {
		fprintf(stderr, "Cannot send '%s': variable not defined\n",
									var);
		return;
	}
	env_opt_start_info();
	env_opt_add(ep->var);
	env_opt_end(0);
}
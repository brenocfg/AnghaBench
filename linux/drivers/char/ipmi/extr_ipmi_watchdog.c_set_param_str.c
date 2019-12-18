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
struct kernel_param {int /*<<< orphan*/  arg; } ;
typedef  int (* action_fn ) (char*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_HB_IF_NECESSARY ; 
 int /*<<< orphan*/  check_parms () ; 
 int ipmi_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strstrip (char*) ; 
 scalar_t__ watchdog_user ; 

__attribute__((used)) static int set_param_str(const char *val, const struct kernel_param *kp)
{
	action_fn  fn = (action_fn) kp->arg;
	int        rv = 0;
	char       valcp[16];
	char       *s;

	strncpy(valcp, val, 15);
	valcp[15] = '\0';

	s = strstrip(valcp);

	rv = fn(s, NULL);
	if (rv)
		goto out;

	check_parms();
	if (watchdog_user)
		rv = ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

 out:
	return rv;
}
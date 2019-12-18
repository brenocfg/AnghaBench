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
struct jailparam {int /*<<< orphan*/ * jp_value; int /*<<< orphan*/ * jp_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  JAIL_ERRMSGLEN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  jail_errmsg ; 
 int /*<<< orphan*/  jailparam_free (struct jailparam*,int) ; 
 scalar_t__ jailparam_type (struct jailparam*) ; 
 int /*<<< orphan*/  memset (struct jailparam*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
jailparam_init(struct jailparam *jp, const char *name)
{

	memset(jp, 0, sizeof(*jp));
	jp->jp_name = strdup(name);
	if (jp->jp_name == NULL) {
		strerror_r(errno, jail_errmsg, JAIL_ERRMSGLEN);
		return (-1);
	}
	if (jailparam_type(jp) < 0) {
		jailparam_free(jp, 1);
		jp->jp_name = NULL;
		jp->jp_value = NULL;
		return (-1);
	}
	return (0);
}
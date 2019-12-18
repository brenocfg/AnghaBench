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
struct sysctl_oid {int dummy; } ;
struct bool_flags {unsigned int flag; char* name; char* noname; } ;
struct TYPE_2__ {unsigned int pr_allow; int /*<<< orphan*/  pr_mtx; } ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  M_PRISON ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  OID_AUTO ; 
 unsigned int PR_ALLOW_ALL_STATIC ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 scalar_t__ asprintf (char**,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nitems (struct bool_flags*) ; 
 struct bool_flags* pr_flag_allow ; 
 TYPE_1__ prison0 ; 
 scalar_t__ strcmp (char*,char*) ; 
 struct sysctl_oid sysctl___security_jail ; 
 struct sysctl_oid sysctl___security_jail_param_allow ; 
 int /*<<< orphan*/  sysctl_jail_default_allow ; 
 int /*<<< orphan*/  sysctl_jail_param ; 

unsigned
prison_add_allow(const char *prefix, const char *name, const char *prefix_descr,
    const char *descr)
{
	struct bool_flags *bf;
	struct sysctl_oid *parent;
	char *allow_name, *allow_noname, *allowed;
#ifndef NO_SYSCTL_DESCR
	char *descr_deprecated;
#endif
	unsigned allow_flag;

	if (prefix
	    ? asprintf(&allow_name, M_PRISON, "allow.%s.%s", prefix, name)
		< 0 ||
	      asprintf(&allow_noname, M_PRISON, "allow.%s.no%s", prefix, name)
		< 0
	    : asprintf(&allow_name, M_PRISON, "allow.%s", name) < 0 ||
	      asprintf(&allow_noname, M_PRISON, "allow.no%s", name) < 0) {
		free(allow_name, M_PRISON);
		return 0;
	}

	/*
	 * See if this parameter has already beed added, i.e. a module was
	 * previously loaded/unloaded.
	 */
	mtx_lock(&prison0.pr_mtx);
	for (bf = pr_flag_allow;
	     bf < pr_flag_allow + nitems(pr_flag_allow) && bf->flag != 0;
	     bf++) {
		if (strcmp(bf->name, allow_name) == 0) {
			allow_flag = bf->flag;
			goto no_add;
		}
	}

	/*
	 * Find a free bit in prison0's pr_allow, failing if there are none
	 * (which shouldn't happen as long as we keep track of how many
	 * potential dynamic flags exist).
	 *
	 * Due to per-jail unprivileged process debugging support
	 * using pr_allow, also verify against PR_ALLOW_ALL_STATIC.
	 * prison0 may have unprivileged process debugging unset.
	 */
	for (allow_flag = 1;; allow_flag <<= 1) {
		if (allow_flag == 0)
			goto no_add;
		if (allow_flag & PR_ALLOW_ALL_STATIC)
			continue;
		if ((prison0.pr_allow & allow_flag) == 0)
			break;
	}

	/*
	 * Note the parameter in the next open slot in pr_flag_allow.
	 * Set the flag last so code that checks pr_flag_allow can do so
	 * without locking.
	 */
	for (bf = pr_flag_allow; bf->flag != 0; bf++)
		if (bf == pr_flag_allow + nitems(pr_flag_allow)) {
			/* This should never happen, but is not fatal. */
			allow_flag = 0;
			goto no_add;
		}
	prison0.pr_allow |= allow_flag;
	bf->name = allow_name;
	bf->noname = allow_noname;
	bf->flag = allow_flag;
	mtx_unlock(&prison0.pr_mtx);

	/*
	 * Create sysctls for the paramter, and the back-compat global
	 * permission.
	 */
	parent = prefix
	    ? SYSCTL_ADD_NODE(NULL,
		  SYSCTL_CHILDREN(&sysctl___security_jail_param_allow),
		  OID_AUTO, prefix, 0, 0, prefix_descr)
	    : &sysctl___security_jail_param_allow;
	(void)SYSCTL_ADD_PROC(NULL, SYSCTL_CHILDREN(parent), OID_AUTO,
	    name, CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE,
	    NULL, 0, sysctl_jail_param, "B", descr);
	if ((prefix
	     ? asprintf(&allowed, M_TEMP, "%s_%s_allowed", prefix, name)
	     : asprintf(&allowed, M_TEMP, "%s_allowed", name)) >= 0) {
#ifndef NO_SYSCTL_DESCR
		(void)asprintf(&descr_deprecated, M_TEMP, "%s (deprecated)",
		    descr);
#endif
		(void)SYSCTL_ADD_PROC(NULL,
		    SYSCTL_CHILDREN(&sysctl___security_jail), OID_AUTO, allowed,
		    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, NULL, allow_flag,
		    sysctl_jail_default_allow, "I", descr_deprecated);
#ifndef NO_SYSCTL_DESCR
		free(descr_deprecated, M_TEMP);
#endif
		free(allowed, M_TEMP);
	}
	return allow_flag;

 no_add:
	mtx_unlock(&prison0.pr_mtx);
	free(allow_name, M_PRISON);
	free(allow_noname, M_PRISON);
	return allow_flag;
}
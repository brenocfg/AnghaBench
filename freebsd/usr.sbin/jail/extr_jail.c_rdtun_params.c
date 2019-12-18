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
struct jailparam {int jp_flags; scalar_t__ jp_valuelen; int jp_ctltype; int /*<<< orphan*/ * jp_name; int /*<<< orphan*/ * jp_value; } ;
struct cfjail {int flags; int njp; struct jailparam* jp; int /*<<< orphan*/ * intparams; int /*<<< orphan*/  jid; } ;

/* Variables and functions */
 int CTLTYPE ; 
 int CTLTYPE_STRING ; 
 size_t IP_ALLOW_DYING ; 
 int /*<<< orphan*/  JAIL_DYING ; 
 int JF_RDTUN ; 
 int JP_BOOL ; 
 int JP_NOBOOL ; 
 scalar_t__ JP_RDTUN (struct jailparam*) ; 
 struct jailparam* alloca (int) ; 
 scalar_t__ bool_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  failed (struct cfjail*) ; 
 int /*<<< orphan*/ * jail_errmsg ; 
 int /*<<< orphan*/  jail_warnx (struct cfjail*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jailparam_free (struct jailparam*,int) ; 
 scalar_t__ jailparam_get (struct jailparam*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ jailparam_import_raw (struct jailparam*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ jailparam_init (struct jailparam*,char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
rdtun_params(struct cfjail *j, int dofail)
{
	struct jailparam *jp, *rtparams, *rtjp;
	int nrt, rval;

	if (j->flags & JF_RDTUN)
		return 0;
	j->flags |= JF_RDTUN;
	nrt = 0;
	for (jp = j->jp; jp < j->jp + j->njp; jp++)
		if (JP_RDTUN(jp) && strcmp(jp->jp_name, "jid"))
			nrt++;
	if (nrt == 0)
		return 0;
	rtjp = rtparams = alloca(++nrt * sizeof(struct jailparam));
	if (jailparam_init(rtjp, "jid") < 0 ||
	    jailparam_import_raw(rtjp, &j->jid, sizeof j->jid) < 0) {
		jail_warnx(j, "%s", jail_errmsg);
		exit(1);
	}
	for (jp = j->jp; jp < j->jp + j->njp; jp++)
		if (JP_RDTUN(jp) && strcmp(jp->jp_name, "jid")) {
			*++rtjp = *jp;
			rtjp->jp_value = NULL;
		}
	rval = 0;
	if (jailparam_get(rtparams, nrt,
	    bool_param(j->intparams[IP_ALLOW_DYING]) ? JAIL_DYING : 0) > 0) {
		rtjp = rtparams + 1;
		for (jp = j->jp; rtjp < rtparams + nrt; jp++) {
			if (JP_RDTUN(jp) && strcmp(jp->jp_name, "jid")) {
				if (!((jp->jp_flags & (JP_BOOL | JP_NOBOOL)) &&
				    jp->jp_valuelen == 0 &&
				    *(int *)jp->jp_value) &&
				    !(rtjp->jp_valuelen == jp->jp_valuelen &&
				    !((jp->jp_ctltype & CTLTYPE) ==
				    CTLTYPE_STRING ? strncmp(rtjp->jp_value,
				    jp->jp_value, jp->jp_valuelen) :
				    memcmp(rtjp->jp_value, jp->jp_value,
				    jp->jp_valuelen)))) {
					if (dofail) {
						jail_warnx(j, "%s cannot be "
						    "changed after creation",
						    jp->jp_name);
						failed(j);
						rval = -1;
					} else
						rval = 1;
					break;
				}
				rtjp++;
			}
		}
	}
	for (rtjp = rtparams + 1; rtjp < rtparams + nrt; rtjp++)
		rtjp->jp_name = NULL;
	jailparam_free(rtparams, nrt);
	return rval;
}
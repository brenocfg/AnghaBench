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
struct pmcstat_target {int pt_pid; } ;
struct kinfo_proc {int ki_pid; int /*<<< orphan*/  ki_comm; } ;
typedef  int /*<<< orphan*/  regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_2__ {int /*<<< orphan*/  pa_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  KERN_PROC_PROC ; 
 int REG_EXTENDED ; 
 int REG_NOMATCH ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pmcstat_target*,int /*<<< orphan*/ ) ; 
 int _POSIX2_LINE_MAX ; 
 TYPE_1__ args ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 struct kinfo_proc* kvm_getprocs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * kvm_openfiles (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct pmcstat_target* malloc (int) ; 
 int /*<<< orphan*/ * pmcstat_kvm ; 
 struct kinfo_proc* pmcstat_plist ; 
 int /*<<< orphan*/  pt_next ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int regexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

void
pmcstat_find_targets(const char *spec)
{
	int n, nproc, pid, rv;
	struct pmcstat_target *pt;
	char errbuf[_POSIX2_LINE_MAX], *end;
	static struct kinfo_proc *kp;
	regex_t reg;
	regmatch_t regmatch;

	/* First check if we've been given a process id. */
      	pid = strtol(spec, &end, 0);
	if (end != spec && pid >= 0) {
		if ((pt = malloc(sizeof(*pt))) == NULL)
			goto outofmemory;
		pt->pt_pid = pid;
		SLIST_INSERT_HEAD(&args.pa_targets, pt, pt_next);
		return;
	}

	/* Otherwise treat arg as a regular expression naming processes. */
	if (pmcstat_kvm == NULL) {
		if ((pmcstat_kvm = kvm_openfiles(NULL, "/dev/null", NULL, 0,
		    errbuf)) == NULL)
			err(EX_OSERR, "ERROR: Cannot open kernel \"%s\"",
			    errbuf);
		if ((pmcstat_plist = kvm_getprocs(pmcstat_kvm, KERN_PROC_PROC,
		    0, &nproc)) == NULL)
			err(EX_OSERR, "ERROR: Cannot get process list: %s",
			    kvm_geterr(pmcstat_kvm));
	} else
		nproc = 0;

	if ((rv = regcomp(&reg, spec, REG_EXTENDED|REG_NOSUB)) != 0) {
		regerror(rv, &reg, errbuf, sizeof(errbuf));
		err(EX_DATAERR, "ERROR: Failed to compile regex \"%s\": %s",
		    spec, errbuf);
	}

	for (n = 0, kp = pmcstat_plist; n < nproc; n++, kp++) {
		if ((rv = regexec(&reg, kp->ki_comm, 1, &regmatch, 0)) == 0) {
			if ((pt = malloc(sizeof(*pt))) == NULL)
				goto outofmemory;
			pt->pt_pid = kp->ki_pid;
			SLIST_INSERT_HEAD(&args.pa_targets, pt, pt_next);
		} else if (rv != REG_NOMATCH) {
			regerror(rv, &reg, errbuf, sizeof(errbuf));
			errx(EX_SOFTWARE, "ERROR: Regex evalation failed: %s",
			    errbuf);
		}
	}

	regfree(&reg);

	return;

 outofmemory:
	errx(EX_SOFTWARE, "Out of memory.");
	/*NOTREACHED*/
}
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
struct jobspec {int startnum; int endrange; int /*<<< orphan*/ * matcheduser; int /*<<< orphan*/ * wanteduser; int /*<<< orphan*/  matchcnt; int /*<<< orphan*/ * wantedhost; } ;
struct jobqueue {char* job_cfname; int job_matched; } ;
struct cjobinfo {char const* cji_acctuser; } ;

/* Variables and functions */
 int calc_jobnum (char*,char const**) ; 
 int /*<<< orphan*/  ctl_freeinf (struct cjobinfo*) ; 
 struct cjobinfo* ctl_readcf (char*,char*) ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int
match_jobspec(struct jobqueue *jq, struct jobspec *jspec)
{
	struct cjobinfo *cfinf;
	const char *cf_hoststr;
	int jnum, match;

#if DEBUG_SCANJS
	printf("\t [ match-js checking %s ]\n", jq->job_cfname);
#endif

	if (jspec == NULL || jq == NULL)
		return (0);

	/*
	 * Keep track of which jobs have already been matched by this
	 * routine, and thus (probably) already processed.
	 */
	if (jq->job_matched)
		return (0);

	jnum = calc_jobnum(jq->job_cfname, &cf_hoststr);
	cfinf = NULL;
	match = 0;			/* assume the job will not match */
	jspec->matcheduser = NULL;

	/*
	 * Check the job-number range.
	 */ 
	if (jspec->startnum >= 0) {
		if (jnum < jspec->startnum)
			goto nomatch;
		if (jnum > jspec->endrange)
			goto nomatch;
	}

	/*
	 * Check the hostname.  Strictly speaking this should be done by
	 * reading the control file, but it is less expensive to check
	 * the hostname-part of the control file name.  Also, this value
	 * can be easily seen in 'lpq -l', while there is no easy way for
	 * a user/operator to see the hostname in the control file.
	 */
	if (jspec->wantedhost != NULL) {
		if (fnmatch(jspec->wantedhost, cf_hoststr, 0) != 0)
			goto nomatch;
	}

	/*
	 * Check for a match on the user name.  This has to be done
	 * by reading the control file.
	 */
	if (jspec->wanteduser != NULL) {
		cfinf = ctl_readcf("fakeq", jq->job_cfname);
		if (cfinf == NULL)
			goto nomatch;
		if (fnmatch(jspec->wanteduser, cfinf->cji_acctuser, 0) != 0)
			goto nomatch;
	}

	/* This job matches all of the specified criteria. */
	match = 1;
	jq->job_matched = 1;		/* avoid matching the job twice */
	jspec->matchcnt++;
	if (jspec->wanteduser != NULL) {
		/*
		 * If the user specified a userid (which may have been a
		 * pattern), then the caller's "doentry()" routine might
		 * want to know the userid of this job that matched.
		 */
		jspec->matcheduser = strdup(cfinf->cji_acctuser);
	}
#if DEBUG_SCANJS
	printf("\t [ job matched! ]\n");
#endif

nomatch:
	if (cfinf != NULL)
		ctl_freeinf(cfinf);
	return (match);
}
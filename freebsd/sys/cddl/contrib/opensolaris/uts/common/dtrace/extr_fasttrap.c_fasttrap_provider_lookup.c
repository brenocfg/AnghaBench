#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  provname ;
struct TYPE_12__ {int /*<<< orphan*/ * p_ucred; int /*<<< orphan*/  p_dtrace_probes; } ;
typedef  TYPE_1__ proc_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_13__ {scalar_t__ ftp_pid; int /*<<< orphan*/  ftp_mtx; struct TYPE_13__* ftp_next; int /*<<< orphan*/  ftp_provid; int /*<<< orphan*/  ftp_name; int /*<<< orphan*/  ftp_retired; int /*<<< orphan*/ * ftp_proc; int /*<<< orphan*/  ftp_cmtx; } ;
typedef  TYPE_2__ fasttrap_provider_t ;
struct TYPE_14__ {int /*<<< orphan*/  ftb_mtx; TYPE_2__* ftb_data; } ;
typedef  TYPE_3__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_pattr_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_15__ {TYPE_3__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACE_PRIV_OWNER ; 
 int DTRACE_PRIV_PROC ; 
 int DTRACE_PRIV_ZONEOWNER ; 
 int DTRACE_PROVNAMELEN ; 
 size_t FASTTRAP_PROVS_INDEX (scalar_t__,char const*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fasttrap_proc_lookup (scalar_t__) ; 
 int /*<<< orphan*/  fasttrap_provider_free (TYPE_2__*) ; 
 TYPE_6__ fasttrap_provs ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* pfind (scalar_t__) ; 
 int /*<<< orphan*/  const pid_attr ; 
 int /*<<< orphan*/  pid_pops ; 
 int snprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  usdt_pops ; 

__attribute__((used)) static fasttrap_provider_t *
fasttrap_provider_lookup(pid_t pid, const char *name,
    const dtrace_pattr_t *pattr)
{
	fasttrap_provider_t *fp, *new_fp = NULL;
	fasttrap_bucket_t *bucket;
	char provname[DTRACE_PROVNAMELEN];
	proc_t *p;
	cred_t *cred;

	ASSERT(strlen(name) < sizeof (fp->ftp_name));
	ASSERT(pattr != NULL);

	bucket = &fasttrap_provs.fth_table[FASTTRAP_PROVS_INDEX(pid, name)];
	mutex_enter(&bucket->ftb_mtx);

	/*
	 * Take a lap through the list and return the match if we find it.
	 */
	for (fp = bucket->ftb_data; fp != NULL; fp = fp->ftp_next) {
		if (fp->ftp_pid == pid && strcmp(fp->ftp_name, name) == 0 &&
		    !fp->ftp_retired) {
			mutex_enter(&fp->ftp_mtx);
			mutex_exit(&bucket->ftb_mtx);
			return (fp);
		}
	}

	/*
	 * Drop the bucket lock so we don't try to perform a sleeping
	 * allocation under it.
	 */
	mutex_exit(&bucket->ftb_mtx);

	/*
	 * Make sure the process exists, isn't a child created as the result
	 * of a vfork(2), and isn't a zombie (but may be in fork).
	 */
	if ((p = pfind(pid)) == NULL)
		return (NULL);

	/*
	 * Increment p_dtrace_probes so that the process knows to inform us
	 * when it exits or execs. fasttrap_provider_free() decrements this
	 * when we're done with this provider.
	 */
	p->p_dtrace_probes++;

	/*
	 * Grab the credentials for this process so we have
	 * something to pass to dtrace_register().
	 */
	PROC_LOCK_ASSERT(p, MA_OWNED);
	crhold(p->p_ucred);
	cred = p->p_ucred;
	PROC_UNLOCK(p);

	new_fp = kmem_zalloc(sizeof (fasttrap_provider_t), KM_SLEEP);
	new_fp->ftp_pid = pid;
	new_fp->ftp_proc = fasttrap_proc_lookup(pid);
#ifndef illumos
	mutex_init(&new_fp->ftp_mtx, "provider mtx", MUTEX_DEFAULT, NULL);
	mutex_init(&new_fp->ftp_cmtx, "lock on creating", MUTEX_DEFAULT, NULL);
#endif

	ASSERT(new_fp->ftp_proc != NULL);

	mutex_enter(&bucket->ftb_mtx);

	/*
	 * Take another lap through the list to make sure a provider hasn't
	 * been created for this pid while we weren't under the bucket lock.
	 */
	for (fp = bucket->ftb_data; fp != NULL; fp = fp->ftp_next) {
		if (fp->ftp_pid == pid && strcmp(fp->ftp_name, name) == 0 &&
		    !fp->ftp_retired) {
			mutex_enter(&fp->ftp_mtx);
			mutex_exit(&bucket->ftb_mtx);
			fasttrap_provider_free(new_fp);
			crfree(cred);
			return (fp);
		}
	}

	(void) strcpy(new_fp->ftp_name, name);

	/*
	 * Fail and return NULL if either the provider name is too long
	 * or we fail to register this new provider with the DTrace
	 * framework. Note that this is the only place we ever construct
	 * the full provider name -- we keep it in pieces in the provider
	 * structure.
	 */
	if (snprintf(provname, sizeof (provname), "%s%u", name, (uint_t)pid) >=
	    sizeof (provname) ||
	    dtrace_register(provname, pattr,
	    DTRACE_PRIV_PROC | DTRACE_PRIV_OWNER | DTRACE_PRIV_ZONEOWNER, cred,
	    pattr == &pid_attr ? &pid_pops : &usdt_pops, new_fp,
	    &new_fp->ftp_provid) != 0) {
		mutex_exit(&bucket->ftb_mtx);
		fasttrap_provider_free(new_fp);
		crfree(cred);
		return (NULL);
	}

	new_fp->ftp_next = bucket->ftb_data;
	bucket->ftb_data = new_fp;

	mutex_enter(&new_fp->ftp_mtx);
	mutex_exit(&bucket->ftb_mtx);

	crfree(cred);
	return (new_fp);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ftp_marked; scalar_t__ ftp_ccount; scalar_t__ ftp_mcount; scalar_t__ ftp_rcount; struct TYPE_5__* ftp_next; int /*<<< orphan*/  ftp_provid; int /*<<< orphan*/  ftp_mtx; int /*<<< orphan*/  ftp_retired; } ;
typedef  TYPE_1__ fasttrap_provider_t ;
struct TYPE_6__ {int /*<<< orphan*/  ftb_mtx; int /*<<< orphan*/  ftb_data; } ;
typedef  TYPE_2__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_provider_id_t ;
struct TYPE_7__ {int fth_nent; TYPE_2__* fth_table; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dtrace_condense (int /*<<< orphan*/ ) ; 
 int dtrace_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_cleanup_cv ; 
 scalar_t__ fasttrap_cleanup_drain ; 
 int /*<<< orphan*/  fasttrap_cleanup_mtx ; 
 scalar_t__ fasttrap_cleanup_work ; 
 int fasttrap_max ; 
 int /*<<< orphan*/  fasttrap_provider_free (TYPE_1__*) ; 
 TYPE_3__ fasttrap_provs ; 
 int fasttrap_total ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
fasttrap_pid_cleanup_cb(void *data)
{
	fasttrap_provider_t **fpp, *fp;
	fasttrap_bucket_t *bucket;
	dtrace_provider_id_t provid;
	int i, later = 0, rval;

	mtx_lock(&fasttrap_cleanup_mtx);
	while (!fasttrap_cleanup_drain || later > 0) {
		fasttrap_cleanup_work = 0;
		mtx_unlock(&fasttrap_cleanup_mtx);

		later = 0;

		/*
		 * Iterate over all the providers trying to remove the marked
		 * ones. If a provider is marked but not retired, we just
		 * have to take a crack at removing it -- it's no big deal if
		 * we can't.
		 */
		for (i = 0; i < fasttrap_provs.fth_nent; i++) {
			bucket = &fasttrap_provs.fth_table[i];
			mutex_enter(&bucket->ftb_mtx);
			fpp = (fasttrap_provider_t **)&bucket->ftb_data;

			while ((fp = *fpp) != NULL) {
				if (!fp->ftp_marked) {
					fpp = &fp->ftp_next;
					continue;
				}

				mutex_enter(&fp->ftp_mtx);

				/*
				 * If this provider has consumers actively
				 * creating probes (ftp_ccount) or is a USDT
				 * provider (ftp_mcount), we can't unregister
				 * or even condense.
				 */
				if (fp->ftp_ccount != 0 ||
				    fp->ftp_mcount != 0) {
					mutex_exit(&fp->ftp_mtx);
					fp->ftp_marked = 0;
					continue;
				}

				if (!fp->ftp_retired || fp->ftp_rcount != 0)
					fp->ftp_marked = 0;

				mutex_exit(&fp->ftp_mtx);

				/*
				 * If we successfully unregister this
				 * provider we can remove it from the hash
				 * chain and free the memory. If our attempt
				 * to unregister fails and this is a retired
				 * provider, increment our flag to try again
				 * pretty soon. If we've consumed more than
				 * half of our total permitted number of
				 * probes call dtrace_condense() to try to
				 * clean out the unenabled probes.
				 */
				provid = fp->ftp_provid;
				if ((rval = dtrace_unregister(provid)) != 0) {
					if (fasttrap_total > fasttrap_max / 2)
						(void) dtrace_condense(provid);

					if (rval == EAGAIN)
						fp->ftp_marked = 1;

					later += fp->ftp_marked;
					fpp = &fp->ftp_next;
				} else {
					*fpp = fp->ftp_next;
					fasttrap_provider_free(fp);
				}
			}
			mutex_exit(&bucket->ftb_mtx);
		}
		mtx_lock(&fasttrap_cleanup_mtx);

		/*
		 * If we were unable to retire a provider, try again after a
		 * second. This situation can occur in certain circumstances
		 * where providers cannot be unregistered even though they have
		 * no probes enabled because of an execution of dtrace -l or
		 * something similar.
		 */
		if (later > 0 || fasttrap_cleanup_work ||
		    fasttrap_cleanup_drain) {
			mtx_unlock(&fasttrap_cleanup_mtx);
			pause("ftclean", hz);
			mtx_lock(&fasttrap_cleanup_mtx);
		} else
			mtx_sleep(&fasttrap_cleanup_cv, &fasttrap_cleanup_mtx,
			    0, "ftcl", 0);
	}

	/*
	 * Wake up the thread in fasttrap_unload() now that we're done.
	 */
	wakeup(&fasttrap_cleanup_drain);
	mtx_unlock(&fasttrap_cleanup_mtx);

	kthread_exit();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct daemon {int num; int /*<<< orphan*/ * cfg; int /*<<< orphan*/ * dnscenv; int /*<<< orphan*/ * dtenv; int /*<<< orphan*/  superalloc; int /*<<< orphan*/ * workers; int /*<<< orphan*/  rc; TYPE_2__* env; int /*<<< orphan*/ * views; int /*<<< orphan*/ * respip_set; int /*<<< orphan*/ * local_zones; } ;
struct TYPE_4__ {scalar_t__ auth_zones; int /*<<< orphan*/ * msg_cache; TYPE_1__* rrset_cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_clear_special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auth_zones_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  daemon_remote_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnsc_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zones_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (struct daemon*) ; 
 int /*<<< orphan*/  log_thread_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  respip_set_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handling_record () ; 
 int /*<<< orphan*/  slabhash_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  views_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_delete (int /*<<< orphan*/ ) ; 

void 
daemon_cleanup(struct daemon* daemon)
{
	int i;
	log_assert(daemon);
	/* before stopping main worker, handle signals ourselves, so we
	   don't die on multiple reload signals for example. */
	signal_handling_record();
	log_thread_set(NULL);
	/* clean up caches because
	 * a) RRset IDs will be recycled after a reload, causing collisions
	 * b) validation config can change, thus rrset, msg, keycache clear */
	slabhash_clear(&daemon->env->rrset_cache->table);
	slabhash_clear(daemon->env->msg_cache);
	local_zones_delete(daemon->local_zones);
	daemon->local_zones = NULL;
	respip_set_delete(daemon->respip_set);
	daemon->respip_set = NULL;
	views_delete(daemon->views);
	daemon->views = NULL;
	if(daemon->env->auth_zones)
		auth_zones_cleanup(daemon->env->auth_zones);
	/* key cache is cleared by module desetup during next daemon_fork() */
	daemon_remote_clear(daemon->rc);
	for(i=0; i<daemon->num; i++)
		worker_delete(daemon->workers[i]);
	free(daemon->workers);
	daemon->workers = NULL;
	daemon->num = 0;
	alloc_clear_special(&daemon->superalloc);
#ifdef USE_DNSTAP
	dt_delete(daemon->dtenv);
	daemon->dtenv = NULL;
#endif
#ifdef USE_DNSCRYPT
	dnsc_delete(daemon->dnscenv);
	daemon->dnscenv = NULL;
#endif
	daemon->cfg = NULL;
}
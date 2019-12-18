#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* rrset_cache; int /*<<< orphan*/ * msg_cache; TYPE_7__* now_tv; } ;
struct worker {int thread_num; TYPE_6__* daemon; TYPE_9__ env; } ;
struct ub_stats_info {double mesh_time_median; } ;
struct TYPE_14__ {long long msg; long long rrset; long long dnscrypt_shared_secret; long long dnscrypt_nonce; long long val; long long iter; long long respip; long long subnet; long long ipsecmod; } ;
struct TYPE_11__ {long long now_sec; long long now_usec; int /*<<< orphan*/  elapsed_usec; int /*<<< orphan*/  elapsed_sec; int /*<<< orphan*/  up_usec; int /*<<< orphan*/  up_sec; } ;
struct ub_shm_stat_info {TYPE_5__ mem; TYPE_2__ time; } ;
struct TYPE_17__ {scalar_t__ tv_sec; } ;
struct TYPE_16__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_15__ {scalar_t__ num; TYPE_4__* dnscenv; TYPE_8__ time_last_stat; TYPE_8__ time_boot; TYPE_1__* shm_info; } ;
struct TYPE_13__ {int /*<<< orphan*/ * nonces_cache; int /*<<< orphan*/ * shared_secrets_cache; } ;
struct TYPE_12__ {int /*<<< orphan*/  table; } ;
struct TYPE_10__ {struct ub_shm_stat_info* ptr_ctl; struct ub_stats_info* ptr_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_DETAIL ; 
 int /*<<< orphan*/  memset (struct ub_stats_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mod_get_mem (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  server_stats_add (struct ub_stats_info*,struct ub_stats_info*) ; 
 int /*<<< orphan*/  server_stats_compile (struct worker*,struct ub_stats_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ slabhash_get_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_timeval_subtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,TYPE_6__*,unsigned int,unsigned int) ; 

void shm_main_run(struct worker *worker)
{
#ifdef HAVE_SHMGET
	struct ub_shm_stat_info *shm_stat;
	struct ub_stats_info *stat_total;
	struct ub_stats_info *stat_info;
	int offset;

	verbose(VERB_DETAIL, "SHM run - worker [%d] - daemon [%p] - timenow(%u) - timeboot(%u)",
		worker->thread_num, worker->daemon, (unsigned)worker->env.now_tv->tv_sec, (unsigned)worker->daemon->time_boot.tv_sec);

	offset = worker->thread_num + 1;
	stat_total = worker->daemon->shm_info->ptr_arr;
	stat_info = worker->daemon->shm_info->ptr_arr + offset;

	/* Copy data to the current position */
	server_stats_compile(worker, stat_info, 0);

	/* First thread, zero fill total, and copy general info */
	if (worker->thread_num == 0) {

		/* Copy data to the current position */
		memset(stat_total, 0, sizeof(struct ub_stats_info));

		/* Point to data into SHM */
		shm_stat = worker->daemon->shm_info->ptr_ctl;
		shm_stat->time.now_sec = (long long)worker->env.now_tv->tv_sec;
		shm_stat->time.now_usec = (long long)worker->env.now_tv->tv_usec;

		stat_timeval_subtract(&shm_stat->time.up_sec, &shm_stat->time.up_usec, worker->env.now_tv, &worker->daemon->time_boot);
		stat_timeval_subtract(&shm_stat->time.elapsed_sec, &shm_stat->time.elapsed_usec, worker->env.now_tv, &worker->daemon->time_last_stat);

		shm_stat->mem.msg = (long long)slabhash_get_mem(worker->env.msg_cache);
		shm_stat->mem.rrset = (long long)slabhash_get_mem(&worker->env.rrset_cache->table);
		shm_stat->mem.dnscrypt_shared_secret = 0;
#ifdef USE_DNSCRYPT
		if(worker->daemon->dnscenv) {
			shm_stat->mem.dnscrypt_shared_secret = (long long)slabhash_get_mem(
				worker->daemon->dnscenv->shared_secrets_cache);
			shm_stat->mem.dnscrypt_nonce = (long long)slabhash_get_mem(
				worker->daemon->dnscenv->nonces_cache);
		}
#endif
		shm_stat->mem.val = (long long)mod_get_mem(&worker->env,
			"validator");
		shm_stat->mem.iter = (long long)mod_get_mem(&worker->env,
			"iterator");
		shm_stat->mem.respip = (long long)mod_get_mem(&worker->env,
			"respip");

		/* subnet mem value is available in shm, also when not enabled,
		 * to make the struct easier to memmap by other applications,
		 * independent of the configuration of unbound */
		shm_stat->mem.subnet = 0;
#ifdef CLIENT_SUBNET
		shm_stat->mem.subnet = (long long)mod_get_mem(&worker->env,
			"subnet");
#endif
		/* ipsecmod mem value is available in shm, also when not enabled,
		 * to make the struct easier to memmap by other applications,
		 * independent of the configuration of unbound */
		shm_stat->mem.ipsecmod = 0;
#ifdef USE_IPSECMOD
		shm_stat->mem.ipsecmod = (long long)mod_get_mem(&worker->env,
			"ipsecmod");
#endif
	}

	server_stats_add(stat_total, stat_info);

	/* print the thread statistics */
	stat_total->mesh_time_median /= (double)worker->daemon->num;

#else
	(void)worker;
#endif /* HAVE_SHMGET */
}
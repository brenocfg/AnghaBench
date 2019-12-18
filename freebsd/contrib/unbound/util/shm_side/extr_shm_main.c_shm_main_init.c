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
typedef  void ub_stats_info ;
typedef  void ub_shm_stat_info ;
struct shm_main_info {scalar_t__ key; scalar_t__ id_ctl; scalar_t__ id_arr; void* ptr_ctl; void* ptr_arr; } ;
struct daemon {int num; struct shm_main_info* shm_info; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ stat_interval; scalar_t__ shm_key; int /*<<< orphan*/  shm_enable; } ;

/* Variables and functions */
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int SHM_R ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct shm_main_info*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ shmat (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* shmget (scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int shm_main_init(struct daemon* daemon)
{
#ifdef HAVE_SHMGET
	struct ub_shm_stat_info *shm_stat;
	size_t shm_size;
	
	/* sanitize */
	if(!daemon)
		return 0;
	if(!daemon->cfg->shm_enable)
		return 1;
	if(daemon->cfg->stat_interval == 0)
		log_warn("shm-enable is yes but statistics-interval is 0");

	/* Statistics to maintain the number of thread + total */
	shm_size = (sizeof(struct ub_stats_info) * (daemon->num + 1));

	/* Allocation of needed memory */
	daemon->shm_info = (struct shm_main_info*)calloc(1, shm_size);

	/* Sanitize */
	if(!daemon->shm_info) {
		log_err("shm fail: malloc failure");
		return 0;
	}

	daemon->shm_info->key = daemon->cfg->shm_key;

	/* Check for previous create SHM */
	daemon->shm_info->id_ctl = shmget(daemon->shm_info->key, sizeof(int), SHM_R);
	daemon->shm_info->id_arr = shmget(daemon->shm_info->key + 1, sizeof(int), SHM_R);

	/* Destroy previous SHM */
	if (daemon->shm_info->id_ctl >= 0)
		shmctl(daemon->shm_info->id_ctl, IPC_RMID, NULL);

	/* Destroy previous SHM */
	if (daemon->shm_info->id_arr >= 0)
		shmctl(daemon->shm_info->id_arr, IPC_RMID, NULL);

	/* SHM: Create the segment */
	daemon->shm_info->id_ctl = shmget(daemon->shm_info->key, sizeof(struct ub_shm_stat_info), IPC_CREAT | 0666);

	if (daemon->shm_info->id_ctl < 0)
	{
		log_err("SHM failed(id_ctl) cannot shmget(key %d) %s",
			daemon->shm_info->key, strerror(errno));

		/* Just release memory unused */
		free(daemon->shm_info);

		return 0;
	}

	daemon->shm_info->id_arr = shmget(daemon->shm_info->key + 1, shm_size, IPC_CREAT | 0666);

	if (daemon->shm_info->id_arr < 0)
	{
		log_err("SHM failed(id_arr) cannot shmget(key %d + 1) %s",
			daemon->shm_info->key, strerror(errno));

		/* Just release memory unused */
		free(daemon->shm_info);

		return 0;
	}

	/* SHM: attach the segment  */
	daemon->shm_info->ptr_ctl = (struct ub_shm_stat_info*)
		shmat(daemon->shm_info->id_ctl, NULL, 0);
	if(daemon->shm_info->ptr_ctl == (void *) -1) {
		log_err("SHM failed(ctl) cannot shmat(%d) %s",
			daemon->shm_info->id_ctl, strerror(errno));

		/* Just release memory unused */
		free(daemon->shm_info);

		return 0;
	}

	daemon->shm_info->ptr_arr = (struct ub_stats_info*)
		shmat(daemon->shm_info->id_arr, NULL, 0);

	if (daemon->shm_info->ptr_arr == (void *) -1)
	{
		log_err("SHM failed(arr) cannot shmat(%d) %s",
			daemon->shm_info->id_arr, strerror(errno));

		/* Just release memory unused */
		free(daemon->shm_info);

		return 0;
	}

	/* Zero fill SHM to stand clean while is not filled by other events */
	memset(daemon->shm_info->ptr_ctl, 0, sizeof(struct ub_shm_stat_info));
	memset(daemon->shm_info->ptr_arr, 0, shm_size);

	shm_stat = daemon->shm_info->ptr_ctl;
	shm_stat->num_threads = daemon->num;

#else
	(void)daemon;
#endif /* HAVE_SHMGET */
	return 1;
}
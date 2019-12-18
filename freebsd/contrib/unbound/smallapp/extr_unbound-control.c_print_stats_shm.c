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
typedef  void ub_stats_info ;
typedef  void ub_shm_stat_info ;
struct config_file {int shm_key; } ;

/* Variables and functions */
 int SHM_R ; 
 int SHM_W ; 
 struct config_file* config_create () ; 
 int /*<<< orphan*/  config_delete (struct config_file*) ; 
 int /*<<< orphan*/  config_read (struct config_file*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_stats_shm (struct config_file*,void*,void*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 scalar_t__ shmat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmdt (void*) ; 
 int shmget (int,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_stats_shm(const char* cfgfile)
{
#ifdef HAVE_SHMGET
	struct config_file* cfg;
	struct ub_stats_info* stats;
	struct ub_shm_stat_info* shm_stat;
	int id_ctl, id_arr;
	/* read config */
	if(!(cfg = config_create()))
		fatal_exit("out of memory");
	if(!config_read(cfg, cfgfile, NULL))
		fatal_exit("could not read config file");
	/* get shm segments */
	id_ctl = shmget(cfg->shm_key, sizeof(int), SHM_R|SHM_W);
	if(id_ctl == -1) {
		fatal_exit("shmget(%d): %s", cfg->shm_key, strerror(errno));
	}
	id_arr = shmget(cfg->shm_key+1, sizeof(int), SHM_R|SHM_W);
	if(id_arr == -1) {
		fatal_exit("shmget(%d): %s", cfg->shm_key+1, strerror(errno));
	}
	shm_stat = (struct ub_shm_stat_info*)shmat(id_ctl, NULL, 0);
	if(shm_stat == (void*)-1) {
		fatal_exit("shmat(%d): %s", id_ctl, strerror(errno));
	}
	stats = (struct ub_stats_info*)shmat(id_arr, NULL, 0);
	if(stats == (void*)-1) {
		fatal_exit("shmat(%d): %s", id_arr, strerror(errno));
	}

	/* print the stats */
	do_stats_shm(cfg, stats, shm_stat);

	/* shutdown */
	shmdt(shm_stat);
	shmdt(stats);
	config_delete(cfg);
#else
	(void)cfgfile;
#endif /* HAVE_SHMGET */
}
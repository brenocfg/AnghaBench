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
struct daemon {TYPE_2__* shm_info; TYPE_1__* cfg; } ;
struct TYPE_4__ {scalar_t__ id_ctl; scalar_t__ id_arr; scalar_t__ ptr_arr; scalar_t__ ptr_ctl; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int /*<<< orphan*/  shm_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 int /*<<< orphan*/  shmctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (scalar_t__) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void shm_main_shutdown(struct daemon* daemon)
{
#ifdef HAVE_SHMGET
	/* web are OK, just disabled */
	if(!daemon->cfg->shm_enable)
		return;

	verbose(VERB_DETAIL, "SHM shutdown - KEY [%d] - ID CTL [%d] ARR [%d] - PTR CTL [%p] ARR [%p]",
		daemon->shm_info->key, daemon->shm_info->id_ctl, daemon->shm_info->id_arr, daemon->shm_info->ptr_ctl, daemon->shm_info->ptr_arr);

	/* Destroy previous SHM */
	if (daemon->shm_info->id_ctl >= 0)
		shmctl(daemon->shm_info->id_ctl, IPC_RMID, NULL);

	if (daemon->shm_info->id_arr >= 0)
		shmctl(daemon->shm_info->id_arr, IPC_RMID, NULL);

	if (daemon->shm_info->ptr_ctl)
		shmdt(daemon->shm_info->ptr_ctl);

	if (daemon->shm_info->ptr_arr)
		shmdt(daemon->shm_info->ptr_arr);

#else
	(void)daemon;
#endif /* HAVE_SHMGET */
}
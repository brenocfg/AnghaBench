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

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_SHMFD ; 
 scalar_t__ devfs_alloc_cdp_inode () ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ shm_dev_ino ; 
 int /*<<< orphan*/  shm_dict_lock ; 
 int /*<<< orphan*/  shm_dictionary ; 
 int /*<<< orphan*/  shm_hash ; 
 int /*<<< orphan*/  shm_ino_unr ; 
 int /*<<< orphan*/  shm_timestamp_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
shm_init(void *arg)
{

	mtx_init(&shm_timestamp_lock, "shm timestamps", NULL, MTX_DEF);
	sx_init(&shm_dict_lock, "shm dictionary");
	shm_dictionary = hashinit(1024, M_SHMFD, &shm_hash);
	new_unrhdr64(&shm_ino_unr, 1);
	shm_dev_ino = devfs_alloc_cdp_inode();
	KASSERT(shm_dev_ino > 0, ("shm dev inode not initialized"));
}
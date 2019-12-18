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
struct flock {int /*<<< orphan*/  l_pid; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  getpid () ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
kvp_release_lock(int pool)
{
	struct flock fl = { 0, 0, 0, F_UNLCK, SEEK_SET, 0 };

	fl.l_pid = getpid();

	if (fcntl(kvp_pools[pool].pool_fd, F_SETLK, &fl) == -1) {
		perror("fcntl");
		KVP_LOG(LOG_ERR, "Failed to release the lock pool: %d\n", pool);
		exit(EXIT_FAILURE);
	}
}
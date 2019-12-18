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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m2_str ; 
 int /*<<< orphan*/  pgsize ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 void* shmat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int shmget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmkey ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

void
sharer(void)
{
	int shmid;
	void *shm_buf;

	shmid = shmget(shmkey, pgsize, 0);
	ATF_REQUIRE_MSG(shmid != -1, "receiver: shmget:%d", errno);

	shm_buf = shmat(shmid, NULL, 0);
	ATF_REQUIRE_MSG(shm_buf != (void *) -1, "receiver: shmat: %d", errno);

	printf("%s\n", (const char *)shm_buf);
	
	ATF_REQUIRE_MSG(strcmp((const char *)shm_buf, m2_str) == 0,
	    "receiver: data isn't correct");

	exit(0);
}
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
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_str ; 
 int /*<<< orphan*/  pgsize ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 void* shmat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int shmget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmkey ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
receiver(void)
{
	int shmid;
	void *shm_buf;

	if ((shmid = shmget(shmkey, pgsize, 0)) == -1)
		err(1, "receiver: shmget");

	if ((shm_buf = shmat(shmid, NULL, 0)) == (void *) -1)
		err(1, "receiver: shmat");

	printf("%s\n", (const char *)shm_buf);
	if (strcmp((const char *)shm_buf, m_str) != 0)
		err(1, "receiver: data isn't correct");

	exit(0);
}
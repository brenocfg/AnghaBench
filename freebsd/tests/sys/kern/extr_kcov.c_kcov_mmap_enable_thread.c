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
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int KCOV_ENTRY_SIZE ; 
 int KCOV_MODE_TRACE_PC ; 
 int /*<<< orphan*/  KIOENABLE ; 
 int /*<<< orphan*/  KIOSETBUFSIZE ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PAGE_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open_kcov () ; 
 int /*<<< orphan*/  sem1 ; 
 int /*<<< orphan*/  sem2 ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
kcov_mmap_enable_thread(void *data)
{
	int fd;

	fd = open_kcov();
	*(int *)data = fd;

	ATF_REQUIRE(ioctl(fd, KIOSETBUFSIZE, PAGE_SIZE / KCOV_ENTRY_SIZE) == 0);
	ATF_CHECK(mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
	    fd, 0) != MAP_FAILED);
	ATF_CHECK(ioctl(fd, KIOENABLE, KCOV_MODE_TRACE_PC) == 0);

	sem_post(&sem1);
	sem_wait(&sem2);

	return (NULL);
}
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
struct stat {int dummy; } ;
struct puffs_kargs {int pa_fd; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  kargs ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int ITERATIONS ; 
 int /*<<< orphan*/  MNT_FORCE ; 
 int /*<<< orphan*/  MOUNT_PUFFS ; 
 int /*<<< orphan*/  dacv ; 
 int dafd ; 
 int /*<<< orphan*/  damtx ; 
 int /*<<< orphan*/  fixup (int,struct puffs_kargs*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  respondthread ; 
 int /*<<< orphan*/  rump_init () ; 
 scalar_t__ rump_sys_mkdir (char*,int) ; 
 scalar_t__ rump_sys_mount (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct puffs_kargs*,int) ; 
 int /*<<< orphan*/  rump_sys_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  rump_sys_unmount (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (unsigned long) ; 
 int /*<<< orphan*/  tests_makegarbage (struct puffs_kargs*,int) ; 
 unsigned long time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unfixup (int,struct puffs_kargs*) ; 

__attribute__((used)) static void
testbody(int nfix)
{
	pthread_t pt;
	struct puffs_kargs kargs;
	unsigned long seed;
	int i;

	seed = time(NULL);
	srandom(seed);
	printf("test seeded RNG with %lu\n", seed);

	rump_init();

	pthread_mutex_init(&damtx, NULL);
	pthread_cond_init(&dacv, NULL);
	pthread_create(&pt, NULL, respondthread, NULL);

	ATF_REQUIRE(rump_sys_mkdir("/mnt", 0777) == 0);

	for (i = 0; i < ITERATIONS; i++) {
		tests_makegarbage(&kargs, sizeof(kargs));
		fixup(nfix, &kargs);
		if (rump_sys_mount(MOUNT_PUFFS, "/mnt", 0,
		    &kargs, sizeof(kargs)) == 0) {
			struct stat sb;

			pthread_mutex_lock(&damtx);
			dafd = kargs.pa_fd;
			pthread_cond_signal(&dacv);
			pthread_mutex_unlock(&damtx);

			rump_sys_stat("/mnt", &sb);
			rump_sys_unmount("/mnt", MNT_FORCE);
		}
		unfixup(nfix, &kargs);

		pthread_mutex_lock(&damtx);
		dafd = -1;
		pthread_mutex_unlock(&damtx);
	}
}
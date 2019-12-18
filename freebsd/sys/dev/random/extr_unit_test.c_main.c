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
typedef  int /*<<< orphan*/  thrd_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ra_deinit_alg ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ra_init_alg ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int NUM_THREADS ; 
 int /*<<< orphan*/  ReadCSPRNG ; 
 int /*<<< orphan*/  RunHarvester ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_1__ random_alg_context ; 
 int stopseeding ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int thrd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thrd_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thrd_join (int /*<<< orphan*/ ,int*) ; 
 int thrd_success ; 

int
main(int argc, char *argv[])
{
	thrd_t threads[NUM_THREADS];
	int rc;
	long t;

	random_alg_context.ra_init_alg(NULL);

	for (t = 0; t < NUM_THREADS; t++) {
		printf("In main: creating thread %ld\n", t);
		rc = thrd_create(&threads[t], (t == 0 ? RunHarvester : ReadCSPRNG), NULL);
		if (rc != thrd_success) {
			printf("ERROR; return code from thrd_create() is %d\n", rc);
			exit(-1);
		}
	}

	for (t = 2; t < NUM_THREADS; t++)
		thrd_join(threads[t], &rc);

	stopseeding = 1;

	thrd_join(threads[1], &rc);
	thrd_join(threads[0], &rc);

	random_alg_context.ra_deinit_alg(NULL);

	/* Last thing that main() should do */
	thrd_exit(0);

	return (0);
}
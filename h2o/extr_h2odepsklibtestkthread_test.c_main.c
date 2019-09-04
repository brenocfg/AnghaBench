#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; double member_4; double member_5; double member_6; int w; int h; int* k; int /*<<< orphan*/  member_7; } ;
typedef  TYPE_1__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  compute (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  kt_for (int,int,int /*<<< orphan*/  (*) (TYPE_1__*,int,int /*<<< orphan*/ ),TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	int i, tmp, tot, type = 0, n_threads = 2;
	global_t global = { 10240*100, 800, 600, -2., -1.2, -1.2, 1.2, 0 };
//	global_t global = { 10240*1, 8, 6, -2., -1.2, -1.2, 1.2, 0 };

	if (argc > 1) {
		type = argv[1][0] == 'o'? 2 : argv[1][0] == 'c'? 3 : argv[1][0] == 'n'? 1 : 0;
		if (argv[1][0] >= '0' && argv[1][0] <= '9')
			n_threads = atoi(argv[1]);
	} else {
		fprintf(stderr, "Usage: ./a.out [openmp | cilk | #threads]\n");
	}
	tot = global.w * global.h;
	global.k = calloc(tot, sizeof(int));
	for (i = 0; i < tot; ++i) global.k[i] = -1;
	if (type == 0) {
		kt_for(n_threads, tot, compute, &global);
	} else if (type == 2) {
		#pragma omp parallel for
		for (i = 0; i < tot; ++i)
			compute(&global, i, 0);
	} else if (type == 3) {
		#if HAVE_CILK
		cilk_for (i = 0; i < tot; ++i)
			compute(&global, i, 0);
		#endif
	}
	for (i = tmp = 0; i < tot; ++i) tmp += (global.k[i] < 0);
	free(global.k);
	assert(tmp == 0);
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int cache_nr; } ;

/* Variables and functions */
 int count ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  discard_cache () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getnanotime () ; 
 int /*<<< orphan*/  printf (char*,double,...) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  stdout ; 
 int test_lazy_init_name_hash (TYPE_1__*,int) ; 
 TYPE_1__ the_index ; 

__attribute__((used)) static uint64_t time_runs(int try_threaded)
{
	uint64_t t0, t1, t2;
	uint64_t sum = 0;
	uint64_t avg;
	int nr_threads_used;
	int i;

	for (i = 0; i < count; i++) {
		t0 = getnanotime();
		read_cache();
		t1 = getnanotime();
		nr_threads_used = test_lazy_init_name_hash(&the_index, try_threaded);
		t2 = getnanotime();

		sum += (t2 - t1);

		if (try_threaded && !nr_threads_used)
			die("non-threaded code path used");

		if (nr_threads_used)
			printf("%f %f %d multi %d\n",
				   ((double)(t1 - t0))/1000000000,
				   ((double)(t2 - t1))/1000000000,
				   the_index.cache_nr,
				   nr_threads_used);
		else
			printf("%f %f %d single\n",
				   ((double)(t1 - t0))/1000000000,
				   ((double)(t2 - t1))/1000000000,
				   the_index.cache_nr);
		fflush(stdout);

		discard_cache();
	}

	avg = sum / count;
	if (count > 1)
		printf("avg %f %s\n",
			   (double)avg/1000000000,
			   (try_threaded) ? "multi" : "single");

	return avg;
}
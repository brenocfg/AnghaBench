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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int cache_nr; } ;

/* Variables and functions */
 int analyze ; 
 scalar_t__ analyze_step ; 
 int count ; 
 int /*<<< orphan*/  discard_cache () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ getnanotime () ; 
 int /*<<< orphan*/  printf (char*,int,double,...) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  stdout ; 
 int test_lazy_init_name_hash (TYPE_1__*,int) ; 
 TYPE_1__ the_index ; 

__attribute__((used)) static void analyze_run(void)
{
	uint64_t t1s, t1m, t2s, t2m;
	int cache_nr_limit;
	int nr_threads_used = 0;
	int i;
	int nr;

	read_cache();
	cache_nr_limit = the_index.cache_nr;
	discard_cache();

	nr = analyze;
	while (1) {
		uint64_t sum_single = 0;
		uint64_t sum_multi = 0;
		uint64_t avg_single;
		uint64_t avg_multi;

		if (nr > cache_nr_limit)
			nr = cache_nr_limit;

		for (i = 0; i < count; i++) {
			read_cache();
			the_index.cache_nr = nr; /* cheap truncate of index */
			t1s = getnanotime();
			test_lazy_init_name_hash(&the_index, 0);
			t2s = getnanotime();
			sum_single += (t2s - t1s);
			the_index.cache_nr = cache_nr_limit;
			discard_cache();

			read_cache();
			the_index.cache_nr = nr; /* cheap truncate of index */
			t1m = getnanotime();
			nr_threads_used = test_lazy_init_name_hash(&the_index, 1);
			t2m = getnanotime();
			sum_multi += (t2m - t1m);
			the_index.cache_nr = cache_nr_limit;
			discard_cache();

			if (!nr_threads_used)
				printf("    [size %8d] [single %f]   non-threaded code path used\n",
					   nr, ((double)(t2s - t1s))/1000000000);
			else
				printf("    [size %8d] [single %f] %c [multi %f %d]\n",
					   nr,
					   ((double)(t2s - t1s))/1000000000,
					   (((t2s - t1s) < (t2m - t1m)) ? '<' : '>'),
					   ((double)(t2m - t1m))/1000000000,
					   nr_threads_used);
			fflush(stdout);
		}
		if (count > 1) {
			avg_single = sum_single / count;
			avg_multi = sum_multi / count;
			if (!nr_threads_used)
				printf("avg [size %8d] [single %f]\n",
					   nr,
					   (double)avg_single/1000000000);
			else
				printf("avg [size %8d] [single %f] %c [multi %f %d]\n",
					   nr,
					   (double)avg_single/1000000000,
					   (avg_single < avg_multi ? '<' : '>'),
					   (double)avg_multi/1000000000,
					   nr_threads_used);
			fflush(stdout);
		}

		if (nr >= cache_nr_limit)
			return;
		nr += analyze_step;
	}
}
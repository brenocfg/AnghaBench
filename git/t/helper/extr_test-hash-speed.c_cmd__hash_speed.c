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
struct git_hash_algo {char* name; } ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
typedef  double clock_t ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 double CLOCKS_PER_SEC ; 
 int GIT_HASH_NALGOS ; 
 int GIT_MAX_RAWSZ ; 
 double NUM_SECONDS ; 
 double clock () ; 
 int /*<<< orphan*/  compute_hash (struct git_hash_algo const*,int /*<<< orphan*/ *,unsigned char*,void*,unsigned int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 struct git_hash_algo* hash_algos ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* xcalloc (int,unsigned int) ; 

int cmd__hash_speed(int ac, const char **av)
{
	git_hash_ctx ctx;
	unsigned char hash[GIT_MAX_RAWSZ];
	clock_t initial, start, end;
	unsigned bufsizes[] = { 64, 256, 1024, 8192, 16384 };
	int i;
	void *p;
	const struct git_hash_algo *algo = NULL;

	if (ac == 2) {
		for (i = 1; i < GIT_HASH_NALGOS; i++) {
			if (!strcmp(av[1], hash_algos[i].name)) {
				algo = &hash_algos[i];
				break;
			}
		}
	}
	if (!algo)
		die("usage: test-tool hash-speed algo_name");

	/* Use this as an offset to make overflow less likely. */
	initial = clock();

	printf("algo: %s\n", algo->name);

	for (i = 0; i < ARRAY_SIZE(bufsizes); i++) {
		unsigned long j, kb;
		double kb_per_sec;
		p = xcalloc(1, bufsizes[i]);
		start = end = clock() - initial;
		for (j = 0; ((end - start) / CLOCKS_PER_SEC) < NUM_SECONDS; j++) {
			compute_hash(algo, &ctx, hash, p, bufsizes[i]);

			/*
			 * Only check elapsed time every 128 iterations to avoid
			 * dominating the runtime with system calls.
			 */
			if (!(j & 127))
				end = clock() - initial;
		}
		kb = j * bufsizes[i];
		kb_per_sec = kb / (1024 * ((double)end - start) / CLOCKS_PER_SEC);
		printf("size %u: %lu iters; %lu KiB; %0.2f KiB/s\n", bufsizes[i], j, kb, kb_per_sec);
		free(p);
	}

	exit(0);
}
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
typedef  int uint32_t ;
struct timeval {double tv_usec; scalar_t__ tv_sec; } ;
struct rusage {struct timeval ru_utime; } ;
struct mbuf {int m_len; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  __USE (int) ; 
 struct mbuf* allocate_mbuf_chain (char**) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int cpu_in_cksum (struct mbuf*,int,int,int) ; 
 int /*<<< orphan*/  dump_mbuf (struct mbuf*,int,int) ; 
 int /*<<< orphan*/  errx (int,char*,int,...) ; 
 int /*<<< orphan*/  free_mbuf_chain (struct mbuf*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getprogname () ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int mbuf_len (struct mbuf*) ; 
 int /*<<< orphan*/  optarg ; 
 int portable_cpu_in_cksum (struct mbuf*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int rand () ; 
 void* random_aligned ; 
 int /*<<< orphan*/  randomise_mbuf_chain (struct mbuf*) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 

int
main(int argc, char **argv)
{
	struct rusage res;
	struct timeval tv, old_tv;
	int loops, old_sum, off, len;
#ifdef HAVE_CPU_IN_CKSUM
	int new_sum;
#endif
	long i, iterations;
	uint32_t init_sum;
	struct mbuf *m;
	bool verbose;
	int c;

	loops = 16;
	verbose = false;
	random_aligned = 0;
	iterations = 100000;

	while ((c = getopt(argc, argv, "i:l:u:v")) != -1) {
		switch (c) {
		case 'i':
			iterations = atoi(optarg);
			break;
		case 'l':
			loops = atoi(optarg);
			break;
		case 'u':
			random_aligned = atoi(optarg);
			break;
		case 'v':
			verbose = true;
			break;
		default:
			errx(1, "%s [-l <loops>] [-u <unalign> [-i <iterations> "
			    "[<mbuf-size> ...]", getprogname());
		}
	}

	for (; loops; --loops) {
		if ((m = allocate_mbuf_chain(argv + 4)) == NULL)
			continue;
		randomise_mbuf_chain(m);
		init_sum = rand();
		len = mbuf_len(m);

		/* force one loop over all data */
		if (loops == 1)
			off = 0;
		else
			off = len ? rand() % len : 0;

		len -= off;
		old_sum = portable_cpu_in_cksum(m, len, off, init_sum);
#ifdef HAVE_CPU_IN_CKSUM
#ifdef MBUFDUMP
		printf("m->m_len=%d len=%d off=%d\n", m->m_len, len, off);
		dump_mbuf(m, len, off);
#endif
		new_sum = cpu_in_cksum(m, len, off, init_sum);
		if (old_sum != new_sum)
			errx(1, "comparison failed: %x %x", old_sum, new_sum);
#else
		__USE(old_sum);
#endif

		if (iterations == 0)
			continue;

		getrusage(RUSAGE_SELF, &res);
		tv = res.ru_utime;
		for (i = iterations; i; --i)
			(void)portable_cpu_in_cksum(m, len, off, init_sum);
		getrusage(RUSAGE_SELF, &res);
		timersub(&res.ru_utime, &tv, &old_tv);
		if (verbose)
			printf("portable version: %jd.%06jd\n",
			    (intmax_t)old_tv.tv_sec, (intmax_t)old_tv.tv_usec);

#ifdef HAVE_CPU_IN_CKSUM
		getrusage(RUSAGE_SELF, &res);
		tv = res.ru_utime;
		for (i = iterations; i; --i)
			(void)cpu_in_cksum(m, len, off, init_sum);
		getrusage(RUSAGE_SELF, &res);
		timersub(&res.ru_utime, &tv, &tv);
		if (verbose) {
			printf("test version:     %jd.%06jd\n",
			    (intmax_t)tv.tv_sec, (intmax_t)tv.tv_usec);
			printf("relative time:    %3.g%%\n",
			    100 * ((double)tv.tv_sec * 1e6 + tv.tv_usec) /
			    ((double)old_tv.tv_sec * 1e6 + old_tv.tv_usec + 1));
		}
#endif
		free_mbuf_chain(m);
	}

	return 0;
}
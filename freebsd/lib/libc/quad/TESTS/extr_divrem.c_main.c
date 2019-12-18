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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  stdin ; 

main()
{
	union { long long q; unsigned long v[2]; } a, b, q, r;
	char buf[300];
	extern long long __qdivrem(unsigned long long, unsigned long long,
	    unsigned long long *);

	for (;;) {
		printf("> ");
		if (fgets(buf, sizeof buf, stdin) == NULL)
			break;
		if (sscanf(buf, "%lu:%lu %lu:%lu",
			    &a.v[0], &a.v[1], &b.v[0], &b.v[1]) != 4 &&
		    sscanf(buf, "0x%lx:%lx 0x%lx:%lx",
			    &a.v[0], &a.v[1], &b.v[0], &b.v[1]) != 4) {
			printf("eh?\n");
			continue;
		}
		q.q = __qdivrem(a.q, b.q, &r.q);
		printf("%lx:%lx /%% %lx:%lx => q=%lx:%lx r=%lx:%lx\n",
		    a.v[0], a.v[1], b.v[0], b.v[1],
		    q.v[0], q.v[1], r.v[0], r.v[1]);
		printf("  = %lX%08lX / %lX%08lX => %lX%08lX\n\
  = %lX%08lX %% %lX%08lX => %lX%08lX\n",
		    a.v[0], a.v[1], b.v[0], b.v[1], q.v[0], q.v[1],
		    a.v[0], a.v[1], b.v[0], b.v[1], r.v[0], r.v[1]);
	}
	exit(0);
}
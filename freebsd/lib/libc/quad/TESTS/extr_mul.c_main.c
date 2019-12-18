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
	union { long long q; unsigned long v[2]; } a, b, m;
	char buf[300];
	extern long long __muldi3(long long, long long);

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
		m.q = __muldi3(a.q, b.q);
		printf("%lx:%lx * %lx:%lx => %lx:%lx\n",
		    a.v[0], a.v[1], b.v[0], b.v[1], m.v[0], m.v[1]);
		printf("  = %lX%08lX * %lX%08lX => %lX%08lX\n",
		    a.v[0], a.v[1], b.v[0], b.v[1], m.v[0], m.v[1]);
	}
	exit(0);
}
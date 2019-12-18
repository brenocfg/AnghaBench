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
struct ch_up_la {int idx; int bufsize; int* data; scalar_t__ stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_GET_UP_LA ; 
 int LA_BUFSIZE ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_up_la*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
get_up_la(int argc, char *argv[], int start_arg, const char *iff_name)
{
	struct ch_up_la la;
	int i, idx, max_idx, entries;

	(void) argc;
	(void) argv;
	(void) start_arg;

	la.stopped = 0;
	la.idx = -1;
	la.bufsize = LA_BUFSIZE;
	la.data = malloc(la.bufsize);
	if (!la.data)
		err(1, "uP_LA malloc");

	if (doit(iff_name, CHELSIO_GET_UP_LA, &la) < 0)
		 err(1, "uP_LA");

	if (la.stopped)
		printf("LA is not running\n");

	entries = la.bufsize / 4;
	idx = (int)la.idx;
	max_idx = (entries / 4) - 1;
	for (i = 0; i < max_idx; i++) {
		printf("%04x %08x %08x\n",
		       la.data[idx], la.data[idx+2], la.data[idx+1]);
		idx = (idx + 4) & (entries - 1);
	}

	return 0;
}
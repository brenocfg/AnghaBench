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
 scalar_t__ FT_PIPE ; 
 scalar_t__ FT_SOCKETPAIR ; 
 char* decode_events (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ filetype ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
report(int num, const char *state, int expected, int got)
{
	if (!expected == !got)
		printf("ok %-2d    ", num);
	else
		printf("not ok %-2d", num);
	printf(" %s state %s: expected %s; got %s\n",
	    filetype == FT_PIPE ? "Pipe" :
	    filetype == FT_SOCKETPAIR ? "Sock" : "FIFO",
	    state, decode_events(expected), decode_events(got));
	fflush(stdout);
}
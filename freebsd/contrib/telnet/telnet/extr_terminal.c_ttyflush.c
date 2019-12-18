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
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  consume; } ;

/* Variables and functions */
 int /*<<< orphan*/  Dump (char,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  NetClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TerminalFlushOutput () ; 
 int TerminalWrite (int /*<<< orphan*/ ,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/  ring_consumed (TYPE_1__*,int) ; 
 int ring_full_consecutive (TYPE_1__*) ; 
 int ring_full_count (TYPE_1__*) ; 
 int /*<<< orphan*/  setcommandmode () ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ termdata ; 
 TYPE_1__ ttyoring ; 

int
ttyflush(int drop)
{
    int n, n0, n1;

    n0 = ring_full_count(&ttyoring);
    if ((n1 = n = ring_full_consecutive(&ttyoring)) > 0) {
	if (drop) {
	    TerminalFlushOutput();
	    /* we leave 'n' alone! */
	} else {
	    n = TerminalWrite(ttyoring.consume, n);
	}
    }
    if (n > 0) {
	if (termdata && n) {
	    Dump('>', ttyoring.consume, n);
	}
	/*
	 * If we wrote everything, and the full count is
	 * larger than what we wrote, then write the
	 * rest of the buffer.
	 */
	if (n1 == n && n0 > n) {
		n1 = n0 - n;
		if (!drop)
			n1 = TerminalWrite(ttyoring.bottom, n1);
		if (n1 > 0)
			n += n1;
	}
	ring_consumed(&ttyoring, n);
    }
    if (n < 0) {
	if (errno == EAGAIN || errno == EINTR) {
	    return -1;
	} else {
	    ring_consumed(&ttyoring, ring_full_count(&ttyoring));
	    setconnmode(0);
	    setcommandmode();
	    NetClose(net);
	    fprintf(stderr, "Write error on local output.\n");
	    exit(1);
	}
	return -1;
    }
    if (n == n0) {
	if (n0)
	    return -1;
	return 0;
    }
    return n0 - n + 1;
}
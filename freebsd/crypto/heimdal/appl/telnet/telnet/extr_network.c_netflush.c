#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ consume; } ;

/* Variables and functions */
 int /*<<< orphan*/  Dump (char,scalar_t__,int) ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int /*<<< orphan*/  NetClose (int /*<<< orphan*/ ) ; 
 scalar_t__ encrypt_output ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net ; 
 scalar_t__ netdata ; 
 TYPE_1__ netoring ; 
 int /*<<< orphan*/  peerdied ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_at_mark (TYPE_1__*) ; 
 int /*<<< orphan*/  ring_clear_mark (TYPE_1__*) ; 
 int /*<<< orphan*/  ring_consumed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ring_encrypt (TYPE_1__*,scalar_t__) ; 
 int ring_full_consecutive (TYPE_1__*) ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcommandmode () ; 

int
netflush(void)
{
    int n, n1;

#if	defined(ENCRYPTION)
    if (encrypt_output)
	ring_encrypt(&netoring, encrypt_output);
#endif
    if ((n1 = n = ring_full_consecutive(&netoring)) > 0) {
	if (!ring_at_mark(&netoring)) {
	    n = send(net, (char *)netoring.consume, n, 0); /* normal write */
	} else {
	    /*
	     * In 4.2 (and 4.3) systems, there is some question about
	     * what byte in a sendOOB operation is the "OOB" data.
	     * To make ourselves compatible, we only send ONE byte
	     * out of band, the one WE THINK should be OOB (though
	     * we really have more the TCP philosophy of urgent data
	     * rather than the Unix philosophy of OOB data).
	     */
	    n = send(net, (char *)netoring.consume, 1, MSG_OOB);/* URGENT data */
	}
    }
    if (n < 0) {
	if (errno != ENOBUFS && errno != EWOULDBLOCK) {
	    setcommandmode();
	    perror(hostname);
	    NetClose(net);
	    ring_clear_mark(&netoring);
	    longjmp(peerdied, -1);
	    /*NOTREACHED*/
	}
	n = 0;
    }
    if (netdata && n) {
	Dump('>', netoring.consume, n);
    }
    if (n) {
	ring_consumed(&netoring, n);
	/*
	 * If we sent all, and more to send, then recurse to pick
	 * up the other half.
	 */
	if ((n1 == n) && ring_full_consecutive(&netoring)) {
	    netflush();
	}
	return 1;
    } else {
	return 0;
    }
}
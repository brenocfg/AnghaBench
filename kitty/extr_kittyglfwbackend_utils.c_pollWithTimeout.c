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
struct timespec {long const member_0; long const member_1; } ;
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  nfds_t ;

/* Variables and functions */
 int ppoll (struct pollfd*,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 

int
pollWithTimeout(struct pollfd *fds, nfds_t nfds, double timeout) {
    const long seconds = (long) timeout;
    const long nanoseconds = (long) ((timeout - seconds) * 1e9);
    struct timespec tv = { seconds, nanoseconds };
    return ppoll(fds, nfds, &tv, NULL);
}
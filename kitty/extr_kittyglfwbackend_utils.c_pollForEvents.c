#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* watches; int /*<<< orphan*/  watches_count; int /*<<< orphan*/  fds; } ;
struct TYPE_7__ {int ready; } ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  dispatchEvents (TYPE_2__*) ; 
 int /*<<< orphan*/  dispatchTimers (TYPE_2__*) ; 
 int errno ; 
 double monotonic () ; 
 int poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pollWithTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 double prepareForPoll (TYPE_2__*,double) ; 

int
pollForEvents(EventLoopData *eld, double timeout) {
    int read_ok = 0;
    timeout = prepareForPoll(eld, timeout);
    int result;
    double end_time = monotonic() + timeout;

    while(1) {
        if (timeout >= 0) {
            errno = 0;
            result = pollWithTimeout(eld->fds, eld->watches_count, timeout);
            int saved_errno = errno;
            dispatchTimers(eld);
            if (result > 0) {
                dispatchEvents(eld);
                read_ok = eld->watches[0].ready;
                break;
            }
            timeout = end_time - monotonic();
            if (timeout <= 0) break;
            if (result < 0 && (saved_errno == EINTR || saved_errno == EAGAIN)) continue;
            break;
        } else {
            errno = 0;
            result = poll(eld->fds, eld->watches_count, -1);
            int saved_errno = errno;
            dispatchTimers(eld);
            if (result > 0) {
                dispatchEvents(eld);
                read_ok = eld->watches[0].ready;
            }
            if (result < 0 && (saved_errno == EINTR || saved_errno == EAGAIN)) continue;
            break;
        }
    }
    return read_ok;
}
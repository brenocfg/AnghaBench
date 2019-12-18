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
struct kevent {int data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_socket_drain () ; 
 int /*<<< orphan*/  kevent_socket_fill () ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/ * sockfd ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 

void
test_kevent_socket_get(void)
{
    const char *test_id = "kevent(EVFILT_READ) wait";
    struct kevent kev;

    test_begin(test_id);

    EV_SET(&kev, sockfd[0], EVFILT_READ, EV_ADD, 0, 0, &sockfd[0]);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    kevent_socket_fill();

    kev.data = 1;
    kevent_cmp(&kev, kevent_get(kqfd));

    kevent_socket_drain();
    test_no_kevents();

    kev.flags = EV_DELETE;
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    success();
}
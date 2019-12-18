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
struct kevent {int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int EV_ADD ; 
 int EV_DELETE ; 
 int EV_DISPATCH ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_socket_drain () ; 
 int /*<<< orphan*/  kevent_socket_fill () ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/ * sockfd ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 

void
test_kevent_socket_dispatch(void)
{
    const char *test_id = "kevent(EVFILT_READ, EV_DISPATCH)";

    test_begin(test_id);

    struct kevent kev;

    /* Re-add the watch and make sure no events are pending */
    puts("-- re-adding knote");
    EV_SET(&kev, sockfd[0], EVFILT_READ, EV_ADD | EV_DISPATCH, 0, 0, &sockfd[0]);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);
    test_no_kevents();

    /* The event will occur only once, even though EV_CLEAR is not
       specified. */
    kevent_socket_fill();
    kev.data = 1;
    kevent_cmp(&kev, kevent_get(kqfd));
    test_no_kevents();

    /* Since the knote is disabled, the EV_DELETE operation succeeds. */
    EV_SET(&kev, sockfd[0], EVFILT_READ, EV_DELETE, 0, 0, &sockfd[0]);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    kevent_socket_drain();

    success();
}
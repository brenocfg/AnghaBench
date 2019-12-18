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
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_USER ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  kevent_add (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 

__attribute__((used)) static void
add_and_delete(void)
{
    const char *test_id = "kevent(EVFILT_USER, EV_ADD and EV_DELETE)";
    struct kevent kev;

    test_begin(test_id);

    kevent_add(kqfd, &kev, 1, EVFILT_USER, EV_ADD, 0, 0, NULL);
    test_no_kevents();

    kevent_add(kqfd, &kev, 1, EVFILT_USER, EV_DELETE, 0, 0, NULL);
    test_no_kevents();

    success();
}
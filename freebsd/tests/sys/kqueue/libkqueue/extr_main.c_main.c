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
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_evfilt_proc () ; 
 int /*<<< orphan*/  test_evfilt_read () ; 
 int /*<<< orphan*/  test_evfilt_signal () ; 
 int /*<<< orphan*/  test_evfilt_timer () ; 
 int /*<<< orphan*/  test_evfilt_user () ; 
 int /*<<< orphan*/  test_evfilt_vnode () ; 
 int /*<<< orphan*/  test_kqueue () ; 
 int /*<<< orphan*/  test_kqueue_close () ; 
 int testnum ; 

int 
main(int argc, char **argv)
{
    int test_proc = 1;
    int test_socket = 1;
    int test_signal = 1;
    int test_vnode = 1;
    int test_timer = 1;
#ifdef __FreeBSD__
    int test_user = 1;
#else
    /* XXX-FIXME temporary */
    int test_user = 0;
#endif

    while (argc) {
        if (strcmp(argv[0], "--no-proc") == 0)
            test_proc = 0;
        if (strcmp(argv[0], "--no-socket") == 0)
            test_socket = 0;
        if (strcmp(argv[0], "--no-timer") == 0)
            test_timer = 0;
        if (strcmp(argv[0], "--no-signal") == 0)
            test_signal = 0;
        if (strcmp(argv[0], "--no-vnode") == 0)
            test_vnode = 0;
        if (strcmp(argv[0], "--no-user") == 0)
            test_user = 0;
        argv++;
        argc--;
    }

    /*
     * Some tests fork.  If output is fully buffered,
     * the children inherit some buffered data and flush
     * it when they exit, causing some data to be printed twice.
     * Use line buffering to avoid this problem.
     */
    setlinebuf(stdout);
    setlinebuf(stderr);

    test_kqueue();
    test_kqueue_close();

    if (test_socket) 
        test_evfilt_read();
    if (test_signal) 
        test_evfilt_signal();
    if (test_vnode) 
        test_evfilt_vnode();
#if HAVE_EVFILT_USER
    if (test_user) 
        test_evfilt_user();
#endif
    if (test_timer) 
        test_evfilt_timer();
    if (test_proc) 
        test_evfilt_proc();

    printf("\n---\n"
            "+OK All %d tests completed.\n", testnum - 1);
    return (0);
}
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
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int called ; 
 int /*<<< orphan*/ * child_pair ; 
 int event_add (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
simple_child_read_cb(evutil_socket_t fd, short event, void *arg)
{
	char buf[256];
	int len;

	len = read(fd, buf, sizeof(buf));
	if (write(child_pair[0], "", 1) < 0)
		tt_fail_perror("write");

	if (len) {
		if (!called) {
			if (event_add(arg, NULL) == -1)
				exit(1);
		}
	} else if (called == 1)
		test_ok = 1;

	called++;
}
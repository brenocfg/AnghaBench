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
 int /*<<< orphan*/  TEST1 ; 
 scalar_t__ called ; 
 int /*<<< orphan*/ * pair ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
read_once_cb(evutil_socket_t fd, short event, void *arg)
{
	char buf[256];
	int len;

	len = read(fd, buf, sizeof(buf));

	if (called) {
		test_ok = 0;
	} else if (len) {
		/* Assumes global pair[0] can be used for writing */
		if (write(pair[0], TEST1, strlen(TEST1)+1) < 0) {
			tt_fail_perror("write");
			test_ok = 0;
		} else {
			test_ok = 1;
		}
	}

	called++;
}
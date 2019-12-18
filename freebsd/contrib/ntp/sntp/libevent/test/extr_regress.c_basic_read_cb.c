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
struct basic_cb_args {int /*<<< orphan*/  eb; int /*<<< orphan*/  ev; int /*<<< orphan*/  callcount; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tt_fail_msg (char*) ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 

__attribute__((used)) static void
basic_read_cb(evutil_socket_t fd, short event, void *data)
{
	char buf[256];
	int len;
	struct basic_cb_args *arg = data;

	len = read(fd, buf, sizeof(buf));

	if (len < 0) {
		tt_fail_perror("read (callback)");
	} else {
		switch (arg->callcount++) {
		case 0:	 /* first call: expect to read data; cycle */
			if (len > 0)
				return;

			tt_fail_msg("EOF before data read");
			break;

		case 1:	 /* second call: expect EOF; stop */
			if (len > 0)
				tt_fail_msg("not all data read on first cycle");
			break;

		default:  /* third call: should not happen */
			tt_fail_msg("too many cycles");
		}
	}

	event_del(arg->ev);
	event_base_loopexit(arg->eb, NULL);
}
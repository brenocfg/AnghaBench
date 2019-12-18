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
struct event {int dummy; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  size_t DWORD ;

/* Variables and functions */
 int ReadFile (int /*<<< orphan*/ ,char*,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_loopbreak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (struct event*) ; 
 int /*<<< orphan*/  event_get_base (struct event*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
fifo_read(evutil_socket_t fd, short event, void *arg)
{
	char buf[255];
	int len;
	struct event *ev = arg;
#ifdef _WIN32
	DWORD dwBytesRead;
#endif

	fprintf(stderr, "fifo_read called with fd: %d, event: %d, arg: %p\n",
	    (int)fd, event, arg);
#ifdef _WIN32
	len = ReadFile((HANDLE)fd, buf, sizeof(buf) - 1, &dwBytesRead, NULL);

	/* Check for end of file. */
	if (len && dwBytesRead == 0) {
		fprintf(stderr, "End Of File");
		event_del(ev);
		return;
	}

	buf[dwBytesRead] = '\0';
#else
	len = read(fd, buf, sizeof(buf) - 1);

	if (len <= 0) {
		if (len == -1)
			perror("read");
		else if (len == 0)
			fprintf(stderr, "Connection closed\n");
		event_del(ev);
		event_base_loopbreak(event_get_base(ev));
		return;
	}

	buf[len] = '\0';
#endif
	fprintf(stdout, "Read: %s\n", buf);
}
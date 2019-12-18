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
struct stat {int st_mode; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;
typedef  int evutil_socket_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int) ; 
 int /*<<< orphan*/  CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EEXIST ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SIGINT ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 struct event* event_new (struct event_base*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_self_cbarg () ; 
 struct event* evsignal_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_base*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fifo_read ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  libevent_global_shutdown () ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int mkfifo (char const*,int) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  signal_cb ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char const*) ; 

int
main(int argc, char **argv)
{
	struct event *evfifo;
	struct event_base* base;
#ifdef _WIN32
	HANDLE socket;
	/* Open a file. */
	socket = CreateFileA("test.txt",	/* open File */
			GENERIC_READ,		/* open for reading */
			0,			/* do not share */
			NULL,			/* no security */
			OPEN_EXISTING,		/* existing file only */
			FILE_ATTRIBUTE_NORMAL,	/* normal file */
			NULL);			/* no attr. template */

	if (socket == INVALID_HANDLE_VALUE)
		return 1;

#else
	struct event *signal_int;
	struct stat st;
	const char *fifo = "event.fifo";
	int socket;

	if (lstat(fifo, &st) == 0) {
		if ((st.st_mode & S_IFMT) == S_IFREG) {
			errno = EEXIST;
			perror("lstat");
			exit(1);
		}
	}

	unlink(fifo);
	if (mkfifo(fifo, 0600) == -1) {
		perror("mkfifo");
		exit(1);
	}

	socket = open(fifo, O_RDONLY | O_NONBLOCK, 0);

	if (socket == -1) {
		perror("open");
		exit(1);
	}

	fprintf(stderr, "Write data to %s\n", fifo);
#endif
	/* Initalize the event library */
	base = event_base_new();

	/* Initalize one event */
#ifdef _WIN32
	evfifo = event_new(base, (evutil_socket_t)socket, EV_READ|EV_PERSIST, fifo_read,
                           event_self_cbarg());
#else
	/* catch SIGINT so that event.fifo can be cleaned up */
	signal_int = evsignal_new(base, SIGINT, signal_cb, base);
	event_add(signal_int, NULL);

	evfifo = event_new(base, socket, EV_READ|EV_PERSIST, fifo_read,
                           event_self_cbarg());
#endif

	/* Add it to the active events, without a timeout */
	event_add(evfifo, NULL);

	event_base_dispatch(base);
	event_base_free(base);
#ifdef _WIN32
	CloseHandle(socket);
#else
	close(socket);
	unlink(fifo);
#endif
	libevent_global_shutdown();
	return (0);
}
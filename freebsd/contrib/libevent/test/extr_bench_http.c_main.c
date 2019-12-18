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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct evhttp {int dummy; } ;
struct event_config {int dummy; } ;
struct event_base {int dummy; } ;
typedef  int ev_uint16_t ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_FLAG_STARTUP_IOCP ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  WSAStartup (int,int /*<<< orphan*/ *) ; 
 int* content ; 
 scalar_t__ content_len ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 char* event_base_get_method (struct event_base*) ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,struct timeval*) ; 
 struct event_base* event_base_new_with_config (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 int /*<<< orphan*/  event_config_set_flag (struct event_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_bind_socket (struct evhttp*,char*,int) ; 
 struct evhttp* evhttp_new (struct event_base*) ; 
 int /*<<< orphan*/  evhttp_set_cb (struct evhttp*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evthread_use_windows_threads () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  http_basic_cb ; 
 int /*<<< orphan*/  http_ref_cb ; 
 int* malloc (scalar_t__) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strtol (char*,char**,int) ; 

int
main(int argc, char **argv)
{
	struct event_config *cfg = event_config_new();
	struct event_base *base;
	struct evhttp *http;
	int i;
	int c;
	int use_iocp = 0;
	ev_uint16_t port = 8080;
	char *endptr = NULL;

#ifdef _WIN32
	WSADATA WSAData;
	WSAStartup(0x101, &WSAData);
#else
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return (1);
#endif

	for (i = 1; i < argc; ++i) {
		if (*argv[i] != '-')
			continue;

		c = argv[i][1];

		if ((c == 'p' || c == 'l') && i + 1 >= argc) {
			fprintf(stderr, "-%c requires argument.\n", c);
			exit(1);
		}

		switch (c) {
		case 'p':
			if (i+1 >= argc || !argv[i+1]) {
				fprintf(stderr, "Missing port\n");
				exit(1);
			}
			port = (int)strtol(argv[i+1], &endptr, 10);
			if (*endptr != '\0') {
				fprintf(stderr, "Bad port\n");
				exit(1);
			}
			break;
		case 'l':
			if (i+1 >= argc || !argv[i+1]) {
				fprintf(stderr, "Missing content length\n");
				exit(1);
			}
			content_len = (size_t)strtol(argv[i+1], &endptr, 10);
			if (*endptr != '\0' || content_len == 0) {
				fprintf(stderr, "Bad content length\n");
				exit(1);
			}
			break;
#ifdef _WIN32
		case 'i':
			use_iocp = 1;
#ifdef EVTHREAD_USE_WINDOWS_THREADS_IMPLEMENTED
			evthread_use_windows_threads();
#endif
			event_config_set_flag(cfg,EVENT_BASE_FLAG_STARTUP_IOCP);
			break;
#endif
		default:
			fprintf(stderr, "Illegal argument \"%c\"\n", c);
			exit(1);
		}
	}

	base = event_base_new_with_config(cfg);
	if (!base) {
		fprintf(stderr, "creating event_base failed. Exiting.\n");
		return 1;
	}

	http = evhttp_new(base);

	content = malloc(content_len);
	if (content == NULL) {
		fprintf(stderr, "Cannot allocate content\n");
		exit(1);
	} else {
		int i = 0;
		for (i = 0; i < (int)content_len; ++i)
			content[i] = (i & 255);
	}

	evhttp_set_cb(http, "/ind", http_basic_cb, NULL);
	fprintf(stderr, "/ind - basic content (memory copy)\n");

	evhttp_set_cb(http, "/ref", http_ref_cb, NULL);
	fprintf(stderr, "/ref - basic content (reference)\n");

	fprintf(stderr, "Serving %d bytes on port %d using %s\n",
	    (int)content_len, port,
	    use_iocp? "IOCP" : event_base_get_method(base));

	evhttp_bind_socket(http, "0.0.0.0", port);

#ifdef _WIN32
	if (use_iocp) {
		struct timeval tv={99999999,0};
		event_base_loopexit(base, &tv);
	}
#endif
	event_base_dispatch(base);

#ifdef _WIN32
	WSACleanup();
#endif

	/* NOTREACHED */
	return (0);
}
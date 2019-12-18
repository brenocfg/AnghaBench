#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
struct TYPE_7__ {int /*<<< orphan*/  console_port; int /*<<< orphan*/  console; } ;
typedef  TYPE_2__ osm_subn_opt_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_8__ {int socket; int in_fd; int out_fd; int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; int /*<<< orphan*/  client_type; } ;
typedef  TYPE_3__ osm_console_t ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  OSM_LOCAL_CONSOLE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 
 int /*<<< orphan*/  OSM_LOOPBACK_CONSOLE ; 
 int /*<<< orphan*/  OSM_REMOTE_CONSOLE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 void* fileno (void*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  osm_console_prompt (int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stdin ; 
 void* stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int osm_console_init(osm_subn_opt_t * opt, osm_console_t * p_oct, osm_log_t * p_log)
{
	p_oct->socket = -1;
	strncpy(p_oct->client_type, opt->console, sizeof(p_oct->client_type));

	/* set up the file descriptors for the console */
	if (strcmp(opt->console, OSM_LOCAL_CONSOLE) == 0) {
		p_oct->in = stdin;
		p_oct->out = stdout;
		p_oct->in_fd = fileno(stdin);
		p_oct->out_fd = fileno(stdout);

		osm_console_prompt(p_oct->out);
#ifdef ENABLE_OSM_CONSOLE_LOOPBACK
	} else if (strcmp(opt->console, OSM_LOOPBACK_CONSOLE) == 0
#ifdef ENABLE_OSM_CONSOLE_SOCKET
		   || strcmp(opt->console, OSM_REMOTE_CONSOLE) == 0
#endif
		   ) {
		struct sockaddr_in sin;
		int optval = 1;

		if ((p_oct->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			OSM_LOG(p_log, OSM_LOG_ERROR,
				"ERR 4B01: Failed to open console socket: %s\n",
				strerror(errno));
			return -1;
		}

		if (setsockopt(p_oct->socket, SOL_SOCKET, SO_REUSEADDR,
			       &optval, sizeof(optval))) {
			OSM_LOG(p_log, OSM_LOG_ERROR,
		                "ERR 4B06: Failed to set socket option: %s\n",
		                strerror(errno));
		        return -1;
		}

		sin.sin_family = AF_INET;
		sin.sin_port = htons(opt->console_port);
#ifdef ENABLE_OSM_CONSOLE_SOCKET
		if (strcmp(opt->console, OSM_REMOTE_CONSOLE) == 0)
			sin.sin_addr.s_addr = htonl(INADDR_ANY);
		else
#endif
			sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		if (bind(p_oct->socket, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			OSM_LOG(p_log, OSM_LOG_ERROR,
				"ERR 4B02: Failed to bind console socket: %s\n",
				strerror(errno));
			return -1;
		}
		if (listen(p_oct->socket, 1) < 0) {
			OSM_LOG(p_log, OSM_LOG_ERROR,
				"ERR 4B03: Failed to listen on console socket: %s\n",
				strerror(errno));
			return -1;
		}

		signal(SIGPIPE, SIG_IGN);	/* protect ourselves from closed pipes */
		p_oct->in = NULL;
		p_oct->out = NULL;
		p_oct->in_fd = -1;
		p_oct->out_fd = -1;
		OSM_LOG(p_log, OSM_LOG_INFO,
			"Console listening on port %d\n", opt->console_port);
#endif
	}

	return 0;
}
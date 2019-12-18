#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct stat {int dummy; } ;
struct ssh {int dummy; } ;
struct in_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/ * h_addr_list; } ;
typedef  int /*<<< orphan*/  hostname ;
struct TYPE_7__ {int /*<<< orphan*/  permit_x11_forwarding_flag; } ;
struct TYPE_6__ {scalar_t__ x11_use_localhost; int /*<<< orphan*/  x11_display_offset; int /*<<< orphan*/ * xauth_location; int /*<<< orphan*/  x11_forwarding; } ;
struct TYPE_5__ {int display_number; int* x11_chanids; int screen; void* auth_display; int /*<<< orphan*/ * display; int /*<<< orphan*/  single_connection; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int NI_MAXHOST ; 
 TYPE_4__* auth_opts ; 
 int /*<<< orphan*/  channel_register_cleanup (struct ssh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ gethostname (char*,int) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ options ; 
 int /*<<< orphan*/  packet_send_debug (char*) ; 
 int /*<<< orphan*/  session_close_single_x11 ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int x11_create_display_inet (struct ssh*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*,int**) ; 
 void* xstrdup (char*) ; 

int
session_setup_x11fwd(struct ssh *ssh, Session *s)
{
	struct stat st;
	char display[512], auth_display[512];
	char hostname[NI_MAXHOST];
	u_int i;

	if (!auth_opts->permit_x11_forwarding_flag) {
		packet_send_debug("X11 forwarding disabled by key options.");
		return 0;
	}
	if (!options.x11_forwarding) {
		debug("X11 forwarding disabled in server configuration file.");
		return 0;
	}
	if (options.xauth_location == NULL ||
	    (stat(options.xauth_location, &st) == -1)) {
		packet_send_debug("No xauth program; cannot forward X11.");
		return 0;
	}
	if (s->display != NULL) {
		debug("X11 display already set.");
		return 0;
	}
	if (x11_create_display_inet(ssh, options.x11_display_offset,
	    options.x11_use_localhost, s->single_connection,
	    &s->display_number, &s->x11_chanids) == -1) {
		debug("x11_create_display_inet failed.");
		return 0;
	}
	for (i = 0; s->x11_chanids[i] != -1; i++) {
		channel_register_cleanup(ssh, s->x11_chanids[i],
		    session_close_single_x11, 0);
	}

	/* Set up a suitable value for the DISPLAY variable. */
	if (gethostname(hostname, sizeof(hostname)) < 0)
		fatal("gethostname: %.100s", strerror(errno));
	/*
	 * auth_display must be used as the displayname when the
	 * authorization entry is added with xauth(1).  This will be
	 * different than the DISPLAY string for localhost displays.
	 */
	if (options.x11_use_localhost) {
		snprintf(display, sizeof display, "localhost:%u.%u",
		    s->display_number, s->screen);
		snprintf(auth_display, sizeof auth_display, "unix:%u.%u",
		    s->display_number, s->screen);
		s->display = xstrdup(display);
		s->auth_display = xstrdup(auth_display);
	} else {
#ifdef IPADDR_IN_DISPLAY
		struct hostent *he;
		struct in_addr my_addr;

		he = gethostbyname(hostname);
		if (he == NULL) {
			error("Can't get IP address for X11 DISPLAY.");
			packet_send_debug("Can't get IP address for X11 DISPLAY.");
			return 0;
		}
		memcpy(&my_addr, he->h_addr_list[0], sizeof(struct in_addr));
		snprintf(display, sizeof display, "%.50s:%u.%u", inet_ntoa(my_addr),
		    s->display_number, s->screen);
#else
		snprintf(display, sizeof display, "%.400s:%u.%u", hostname,
		    s->display_number, s->screen);
#endif
		s->display = xstrdup(display);
		s->auth_display = xstrdup(display);
	}

	return 1;
}
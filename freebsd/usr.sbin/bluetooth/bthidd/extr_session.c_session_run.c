#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_l2cap {int /*<<< orphan*/  l2cap_bdaddr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  local ;
typedef  int int32_t ;
typedef  TYPE_2__* hid_device_p ;
typedef  TYPE_3__* bthid_session_p ;
struct TYPE_11__ {scalar_t__ vkbd; scalar_t__ umouse; scalar_t__ ukbd; TYPE_1__* srv; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  ctrl; } ;
struct TYPE_10__ {scalar_t__ keyboard; scalar_t__ mouse; } ;
struct TYPE_9__ {scalar_t__ maxfd; int /*<<< orphan*/  rfdset; scalar_t__ uinput; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_2__* get_hid_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  hid_initialise (TYPE_3__*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uinput_open_keyboard (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ uinput_open_mouse (TYPE_2__*,int /*<<< orphan*/ *) ; 

int32_t
session_run(bthid_session_p s)
{
	hid_device_p d = get_hid_device(&s->bdaddr);
	struct sockaddr_l2cap   local;
	socklen_t               len;

	if (d->keyboard) {
		/* Open /dev/vkbdctl */
		s->vkbd = open("/dev/vkbdctl", O_RDWR);
		if (s->vkbd < 0) {
			syslog(LOG_ERR, "Could not open /dev/vkbdctl " \
				"for %s. %s (%d)", bt_ntoa(&s->bdaddr, NULL),
				strerror(errno), errno);
			return (-1);
		}
		/* Register session's vkbd descriptor (if needed) for read */
		FD_SET(s->vkbd, &s->srv->rfdset);
		if (s->vkbd > s->srv->maxfd)
			s->srv->maxfd = s->vkbd;
	}

	/* Pass device for probing */
	hid_initialise(s);

	/* Take local bdaddr */
	len = sizeof(local);
	getsockname(s->ctrl, (struct sockaddr *) &local, &len);

	if (d->mouse && s->srv->uinput) {
		s->umouse = uinput_open_mouse(d, &local.l2cap_bdaddr);
		if (s->umouse < 0) {
			syslog(LOG_ERR, "Could not open /dev/uinput " \
				"for %s. %s (%d)", bt_ntoa(&s->bdaddr,
				NULL), strerror(errno), errno);
			return (-1);
		}
	}
	if (d->keyboard && s->srv->uinput) {
		s->ukbd = uinput_open_keyboard(d, &local.l2cap_bdaddr);
		if (s->ukbd < 0) {
			syslog(LOG_ERR, "Could not open /dev/uinput " \
				"for %s. %s (%d)", bt_ntoa(&s->bdaddr,
				NULL), strerror(errno), errno);
			return (-1);
		}
		/* Register session's ukbd descriptor (if needed) for read */
		FD_SET(s->ukbd, &s->srv->rfdset);
		if (s->ukbd > s->srv->maxfd)
			s->srv->maxfd = s->ukbd;
	}
	return (0);
}
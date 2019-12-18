#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int socklen_t ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_1__* hid_device_p ;
typedef  int /*<<< orphan*/  error ;
typedef  TYPE_2__* bthid_session_p ;
typedef  TYPE_3__* bthid_server_p ;
struct TYPE_12__ {scalar_t__ maxfd; int /*<<< orphan*/  rfdset; int /*<<< orphan*/  wfdset; } ;
struct TYPE_11__ {int state; scalar_t__ ctrl; int intr; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  new_device; int /*<<< orphan*/  interrupt_psm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int OPEN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
#define  W4CTRL 129 
#define  W4INTR 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int client_socket (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ connect_in_progress ; 
 scalar_t__ errno ; 
 TYPE_1__* get_hid_device (int /*<<< orphan*/ *) ; 
 scalar_t__ getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 TYPE_2__* session_by_fd (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  session_close (TYPE_2__*) ; 
 int /*<<< orphan*/  session_run (TYPE_2__*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_hids_file () ; 

int32_t
client_connect(bthid_server_p srv, int32_t fd)
{
	bthid_session_p	s;
	hid_device_p	d;
	int32_t		error;
	socklen_t	len;

	assert(srv != NULL);
	assert(fd >= 0);

	s = session_by_fd(srv, fd);
	assert(s != NULL);

	d = get_hid_device(&s->bdaddr);
	assert(d != NULL);

	error = 0;
	len = sizeof(error);
	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
		syslog(LOG_ERR, "Could not get socket error for %s. %s (%d)",
			bt_ntoa(&s->bdaddr, NULL), strerror(errno), errno);
		session_close(s);
		connect_in_progress = 0;

		return (-1);
	}

	if (error != 0) {
		syslog(LOG_ERR, "Could not connect to %s. %s (%d)",
			bt_ntoa(&s->bdaddr, NULL), strerror(error), error);
		session_close(s);
		connect_in_progress = 0;

		return (0);
	}

	switch (s->state) {
	case W4CTRL: /* Control channel is open */
		assert(s->ctrl == fd);
		assert(s->intr == -1);

		/* Open interrupt channel */
		s->intr = client_socket(&s->bdaddr, d->interrupt_psm);
		if (s->intr < 0) { 
			syslog(LOG_ERR, "Could not open interrupt channel " \
				"to %s. %s (%d)", bt_ntoa(&s->bdaddr, NULL),
				strerror(errno), errno);
			session_close(s);
			connect_in_progress = 0;

			return (-1);
		}

		s->state = W4INTR;

		FD_SET(s->intr, &srv->wfdset);
		if (s->intr > srv->maxfd)
			srv->maxfd = s->intr;

		d->new_device = 0; /* reset new device flag */
		write_hids_file();
		break;

	case W4INTR: /* Interrupt channel is open */
		assert(s->ctrl != -1);
		assert(s->intr == fd);

		s->state = OPEN;
		connect_in_progress = 0;

		/* Create kbd/mouse after both channels are established */
		if (session_run(s) < 0) {
			session_close(s);
			return (-1);
		}
		break;

	default:
		assert(0);
		break;
	}

	/* Move fd to from the write fd set into read fd set */
	FD_CLR(fd, &srv->wfdset);
	FD_SET(fd, &srv->rfdset);

	return (0);
}
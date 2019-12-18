#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_l2cap {int l2cap_len; void* l2cap_psm; scalar_t__ l2cap_cid; int /*<<< orphan*/  l2cap_bdaddr_type; int /*<<< orphan*/  l2cap_bdaddr; int /*<<< orphan*/  l2cap_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  l2addr ;
typedef  int int32_t ;
typedef  TYPE_1__* bthid_server_p ;
struct TYPE_3__ {int ctrl; int intr; int cons; int /*<<< orphan*/  maxfd; int /*<<< orphan*/  rfdset; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  sessions; int /*<<< orphan*/  wfdset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_L2CAP ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 void* htole16 (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 void* socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t
server_init(bthid_server_p srv)
{
	struct sockaddr_l2cap	l2addr;

	assert(srv != NULL);

	srv->ctrl = srv->intr = -1;
	FD_ZERO(&srv->rfdset);
	FD_ZERO(&srv->wfdset);
	LIST_INIT(&srv->sessions);

	/* Open /dev/consolectl */
	srv->cons = open("/dev/consolectl", O_RDWR);
	if (srv->cons < 0) {
		syslog(LOG_ERR, "Could not open /dev/consolectl. %s (%d)",
			strerror(errno), errno);
		return (-1);
	}

	/* Create control socket */
	srv->ctrl = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BLUETOOTH_PROTO_L2CAP);
	if (srv->ctrl < 0) {
		syslog(LOG_ERR, "Could not create control L2CAP socket. " \
			"%s (%d)", strerror(errno), errno);
		close(srv->cons);
		return (-1);
	}

	l2addr.l2cap_len = sizeof(l2addr);
	l2addr.l2cap_family = AF_BLUETOOTH;
	memcpy(&l2addr.l2cap_bdaddr, &srv->bdaddr, sizeof(l2addr.l2cap_bdaddr));
	l2addr.l2cap_psm = htole16(0x11);
	l2addr.l2cap_bdaddr_type = BDADDR_BREDR;
	l2addr.l2cap_cid = 0;
	
	if (bind(srv->ctrl, (struct sockaddr *) &l2addr, sizeof(l2addr)) < 0) {
		syslog(LOG_ERR, "Could not bind control L2CAP socket. " \
			"%s (%d)", strerror(errno), errno);
		close(srv->ctrl);
		close(srv->cons);
		return (-1);
	}

	if (listen(srv->ctrl, 10) < 0) {
		syslog(LOG_ERR, "Could not listen on control L2CAP socket. " \
			"%s (%d)", strerror(errno), errno);
		close(srv->ctrl);
		close(srv->cons);
		return (-1);
	}

	/* Create intrrupt socket */
	srv->intr = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BLUETOOTH_PROTO_L2CAP);
	if (srv->intr < 0) {
		syslog(LOG_ERR, "Could not create interrupt L2CAP socket. " \
			"%s (%d)", strerror(errno), errno);
		close(srv->ctrl);
		close(srv->cons);
		return (-1);
	}

	l2addr.l2cap_psm = htole16(0x13);

	if (bind(srv->intr, (struct sockaddr *) &l2addr, sizeof(l2addr)) < 0) {
		syslog(LOG_ERR, "Could not bind interrupt L2CAP socket. " \
			"%s (%d)", strerror(errno), errno);
		close(srv->intr);
		close(srv->ctrl);
		close(srv->cons);
		return (-1);
	}

	if (listen(srv->intr, 10) < 0) {
		syslog(LOG_ERR, "Could not listen on interrupt L2CAP socket. "\
			"%s (%d)", strerror(errno), errno);
		close(srv->intr);
		close(srv->ctrl);
		close(srv->cons);
		return (-1);
	}

	FD_SET(srv->ctrl, &srv->rfdset);
	FD_SET(srv->intr, &srv->rfdset);
	srv->maxfd = max(srv->ctrl, srv->intr);

	return (0);
}
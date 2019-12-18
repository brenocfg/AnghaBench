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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_l2cap {int l2cap_len; int /*<<< orphan*/  l2cap_bdaddr; scalar_t__ l2cap_cid; int /*<<< orphan*/  l2cap_bdaddr_type; int /*<<< orphan*/  l2cap_psm; int /*<<< orphan*/  l2cap_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  mru ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_L2CAP ; 
 int /*<<< orphan*/  BNEP_MTU_MIN ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  SOL_L2CAP ; 
 int /*<<< orphan*/  SO_L2CAP_IMTU ; 
 int /*<<< orphan*/  bdaddr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bind (int,struct sockaddr*,int) ; 
 int event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_psm ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bdaddr ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_l2cap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_ev ; 
 int server_fd ; 
 int /*<<< orphan*/  server_read ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
server_open(void)
{
	struct sockaddr_l2cap sa;
	uint16_t mru;

	server_fd = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BLUETOOTH_PROTO_L2CAP);
	if (server_fd == -1) {
		log_err("Could not open L2CAP socket: %m");
		exit(EXIT_FAILURE);
	}

	memset(&sa, 0, sizeof(sa));
	sa.l2cap_family = AF_BLUETOOTH;
	sa.l2cap_len = sizeof(sa);
	sa.l2cap_psm = htole16(l2cap_psm);
	sa.l2cap_bdaddr_type = BDADDR_BREDR;
	sa.l2cap_cid = 0;
	
	bdaddr_copy(&sa.l2cap_bdaddr, &local_bdaddr);
	if (bind(server_fd, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
		log_err("Could not bind server socket: %m");
		exit(EXIT_FAILURE);
	}

	mru = BNEP_MTU_MIN;
	if (setsockopt(server_fd, SOL_L2CAP,
	    SO_L2CAP_IMTU, &mru, sizeof(mru)) == -1) {
		log_err("Could not set L2CAP IMTU (%d): %m", mru);
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 0) == -1) {
		log_err("Could not listen on server socket: %m");
		exit(EXIT_FAILURE);
	}

	event_set(&server_ev, server_fd, EV_READ | EV_PERSIST, server_read, NULL);
	if (event_add(&server_ev, NULL) == -1) {
		log_err("Could not add server event: %m");
		exit(EXIT_FAILURE);
	}

	log_info("server socket open");
}
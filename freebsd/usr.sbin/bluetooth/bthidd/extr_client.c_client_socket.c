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
struct sockaddr_l2cap {int l2cap_len; scalar_t__ l2cap_psm; int /*<<< orphan*/  l2cap_bdaddr; scalar_t__ l2cap_cid; int /*<<< orphan*/  l2cap_bdaddr_type; int /*<<< orphan*/  l2cap_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  l2addr ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  bdaddr_p ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_L2CAP ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ O_NONBLOCK ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 scalar_t__ htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
client_socket(bdaddr_p bdaddr, uint16_t psm)
{
	struct sockaddr_l2cap	l2addr;
	int32_t			s, m;

	s = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BLUETOOTH_PROTO_L2CAP);
	if (s < 0)
		return (-1);

	m = fcntl(s, F_GETFL);
	if (m < 0) {
		close(s);
		return (-1);
	}

	if (fcntl(s, F_SETFL, (m|O_NONBLOCK)) < 0) {
		close(s);
		return (-1);
	}

	l2addr.l2cap_len = sizeof(l2addr);
	l2addr.l2cap_family = AF_BLUETOOTH;
	memset(&l2addr.l2cap_bdaddr, 0, sizeof(l2addr.l2cap_bdaddr));
	l2addr.l2cap_psm = 0;
	l2addr.l2cap_bdaddr_type = BDADDR_BREDR;
	l2addr.l2cap_cid = 0;
	
	if (bind(s, (struct sockaddr *) &l2addr, sizeof(l2addr)) < 0) {
		close(s);
		return (-1);
	}

	memcpy(&l2addr.l2cap_bdaddr, bdaddr, sizeof(l2addr.l2cap_bdaddr));
	l2addr.l2cap_psm = htole16(psm);

	if (connect(s, (struct sockaddr *) &l2addr, sizeof(l2addr)) < 0 &&
	    errno != EINPROGRESS) {
		close(s);
		return (-1);
	}

	return (s);
}
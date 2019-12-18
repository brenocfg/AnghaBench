#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ ng_hci_scodata_pkt_t ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ ng_hci_event_pkt_t ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ ng_hci_cmd_pkt_t ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_4__ ng_hci_acldata_pkt_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
#define  NG_HCI_ACL_DATA_PKT 131 
#define  NG_HCI_CMD_PKT 130 
#define  NG_HCI_EVENT_PKT 129 
#define  NG_HCI_SCO_DATA_PKT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int read (int,void*,size_t) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

ssize_t
bt_devrecv(int s, void *buf, size_t size, time_t to)
{
	ssize_t	n;

	if (buf == NULL || size == 0) {
		errno = EINVAL;
		return (-1);
	}

	if (to >= 0) {
		fd_set		rfd;
		struct timeval	tv;

		FD_ZERO(&rfd);
		FD_SET(s, &rfd);

		tv.tv_sec = to;
		tv.tv_usec = 0;

		while ((n = select(s + 1, &rfd, NULL, NULL, &tv)) < 0) {
			if (errno == EAGAIN || errno == EINTR)
				continue;

			return (-1);
		}

		if (n == 0) {
			errno = ETIMEDOUT;
			return (-1);
		}

		assert(FD_ISSET(s, &rfd));
	}

	while ((n = read(s, buf, size)) < 0) {
		if (errno == EAGAIN || errno == EINTR)
			continue;

		return (-1);
	}

	switch (*((uint8_t *) buf)) {
	case NG_HCI_CMD_PKT: {
		ng_hci_cmd_pkt_t	*h = (ng_hci_cmd_pkt_t *) buf;

		if (n >= sizeof(*h) && n == (sizeof(*h) + h->length))
			return (n);
		} break;

	case NG_HCI_ACL_DATA_PKT: {
		ng_hci_acldata_pkt_t	*h = (ng_hci_acldata_pkt_t *) buf;

		if (n >= sizeof(*h) && n == (sizeof(*h) + le16toh(h->length)))
			return (n);
		} break;

	case NG_HCI_SCO_DATA_PKT: {
		ng_hci_scodata_pkt_t	*h = (ng_hci_scodata_pkt_t *) buf;

		if (n >= sizeof(*h) && n == (sizeof(*h) + h->length))
			return (n);
		} break;

	case NG_HCI_EVENT_PKT: {
		ng_hci_event_pkt_t	*h = (ng_hci_event_pkt_t *) buf;

		if (n >= sizeof(*h) && n == (sizeof(*h) + h->length))
			return (n);
		} break;
	}

	errno = EIO;
	return (-1);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct bt_devreq {scalar_t__ rlen; int event; int /*<<< orphan*/ * rparam; int /*<<< orphan*/  opcode; int /*<<< orphan*/  clen; int /*<<< orphan*/  cparam; } ;
struct bt_devfilter {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ type; int event; int /*<<< orphan*/  status; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ng_hci_event_pkt_t ;
typedef  TYPE_1__ ng_hci_command_status_ep ;
typedef  TYPE_1__ ng_hci_command_compl_ep ;
typedef  int /*<<< orphan*/  new ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
#define  NG_HCI_EVENT_COMMAND_COMPL 129 
#define  NG_HCI_EVENT_COMMAND_STATUS 128 
 scalar_t__ NG_HCI_EVENT_PKT ; 
 scalar_t__ bt_devfilter (int,struct bt_devfilter*,struct bt_devfilter*) ; 
 int /*<<< orphan*/  bt_devfilter_evt_set (struct bt_devfilter*,int) ; 
 int /*<<< orphan*/  bt_devfilter_pkt_set (struct bt_devfilter*,scalar_t__) ; 
 scalar_t__ bt_devrecv (int,int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ bt_devsend (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct bt_devfilter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
bt_devreq(int s, struct bt_devreq *r, time_t to)
{
	uint8_t				buf[320]; /* more than enough */
	ng_hci_event_pkt_t		*e = (ng_hci_event_pkt_t *) buf;
	ng_hci_command_compl_ep		*cc = (ng_hci_command_compl_ep *)(e+1);
	ng_hci_command_status_ep	*cs = (ng_hci_command_status_ep*)(e+1);
	struct bt_devfilter		old, new;
	time_t				t_end;
	uint16_t			opcode;
	ssize_t				n;
	int				error;

	if (s < 0 || r == NULL || to < 0) {
		errno = EINVAL;
		return (-1);
	}

	if ((r->rlen == 0 && r->rparam != NULL) ||
	    (r->rlen > 0 && r->rparam == NULL)) {
		errno = EINVAL;
		return (-1);
	}

	memset(&new, 0, sizeof(new));
	bt_devfilter_pkt_set(&new, NG_HCI_EVENT_PKT);
	bt_devfilter_evt_set(&new, NG_HCI_EVENT_COMMAND_COMPL);
	bt_devfilter_evt_set(&new, NG_HCI_EVENT_COMMAND_STATUS);
	if (r->event != 0)
		bt_devfilter_evt_set(&new, r->event);

	if (bt_devfilter(s, &new, &old) < 0)
		return (-1);

	error = 0;

	n = bt_devsend(s, r->opcode, r->cparam, r->clen);
	if (n < 0) {
		error = errno;
		goto out;	
	}

	opcode = htole16(r->opcode);
	t_end = time(NULL) + to;

	do {
		to = t_end - time(NULL);
		if (to < 0)
			to = 0;

		n = bt_devrecv(s, buf, sizeof(buf), to);
		if (n < 0) {
			error = errno;
			goto out;
		}

		if (e->type != NG_HCI_EVENT_PKT) {
			error = EIO;
			goto out;
		}

		n -= sizeof(*e);

		switch (e->event) {
		case NG_HCI_EVENT_COMMAND_COMPL:
			if (cc->opcode == opcode) {
				n -= sizeof(*cc);

				if (r->rlen >= n) {
					r->rlen = n;
					memcpy(r->rparam, cc + 1, r->rlen);
				}

				goto out;
			}
			break;

		case NG_HCI_EVENT_COMMAND_STATUS:
			if (cs->opcode == opcode) {
				if (r->event != NG_HCI_EVENT_COMMAND_STATUS) {
					if (cs->status != 0) {
						error = EIO;
						goto out;
					}
				} else {
					if (r->rlen >= n) {
						r->rlen = n;
						memcpy(r->rparam, cs, r->rlen);
					}

					goto out;
				}
			}
			break;

		default:
			if (e->event == r->event) {
				if (r->rlen >= n) {
					r->rlen = n;
					memcpy(r->rparam, e + 1, r->rlen);
				}

				goto out;
			}
			break;
		}
	} while (to > 0);

	error = ETIMEDOUT;
out:
	bt_devfilter(s, &old, NULL);

	if (error != 0) {
		errno = error;
		return (-1);
	}

	return (0);
}
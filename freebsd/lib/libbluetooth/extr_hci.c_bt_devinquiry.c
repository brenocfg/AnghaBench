#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int time_t ;
struct bt_devinquiry {int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  pscan_period_mode; int /*<<< orphan*/  pscan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
struct bt_devfilter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_responses; } ;
typedef  TYPE_1__ ng_hci_inquiry_result_ep ;
struct TYPE_7__ {int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  uclass; int /*<<< orphan*/  page_scan_period_mode; int /*<<< orphan*/  page_scan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_2__ ng_hci_inquiry_response ;
struct TYPE_8__ {int* lap; void* num_responses; void* inquiry_length; } ;
typedef  TYPE_3__ ng_hci_inquiry_cp ;
struct TYPE_9__ {int event; } ;
typedef  TYPE_4__ ng_hci_event_pkt_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  _devname ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HCI_DEVNAME_SIZE ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
#define  NG_HCI_EVENT_INQUIRY_COMPL 129 
#define  NG_HCI_EVENT_INQUIRY_RESULT 128 
 int /*<<< orphan*/  NG_HCI_OCF_INQUIRY ; 
 int /*<<< orphan*/  NG_HCI_OGF_LINK_CONTROL ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdaddr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_devany_cb ; 
 int /*<<< orphan*/  bt_devclose (int) ; 
 int bt_devenum (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bt_devfilter (int,struct bt_devfilter*,struct bt_devfilter*) ; 
 int /*<<< orphan*/  bt_devfilter_evt_set (struct bt_devfilter*,int) ; 
 int bt_devopen (char const*) ; 
 int bt_devrecv (int,void**,int,int) ; 
 scalar_t__ bt_devsend (int,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 struct bt_devinquiry* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct bt_devinquiry*) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

int
bt_devinquiry(char const *devname, time_t length, int num_rsp,
		struct bt_devinquiry **ii)
{
	uint8_t				buf[320];
	char				_devname[HCI_DEVNAME_SIZE];
	struct bt_devfilter		f;
	ng_hci_inquiry_cp		*cp = (ng_hci_inquiry_cp *) buf;
	ng_hci_event_pkt_t		*e = (ng_hci_event_pkt_t *) buf;
	ng_hci_inquiry_result_ep	*ep = (ng_hci_inquiry_result_ep *)(e+1);
	ng_hci_inquiry_response		*ir;
	struct bt_devinquiry		*i;
	int				s, n;

	if (ii == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (devname == NULL) {
		memset(_devname, 0, sizeof(_devname));
		devname = _devname;

		n = bt_devenum(bt_devany_cb, _devname);
		if (n <= 0) {
			if (n == 0)
				*ii = NULL;

			return (n);
		}
	}

	s = bt_devopen(devname);
	if (s < 0)
		return (-1);

	if (bt_devfilter(s, NULL, &f) < 0) {
		bt_devclose(s);
		return (-1);
	}

	bt_devfilter_evt_set(&f, NG_HCI_EVENT_INQUIRY_COMPL);
	bt_devfilter_evt_set(&f, NG_HCI_EVENT_INQUIRY_RESULT);

	if (bt_devfilter(s, &f, NULL) < 0) {
		bt_devclose(s);
		return (-1);
	}

	/* Always use GIAC LAP */
	cp->lap[0] = 0x33;
	cp->lap[1] = 0x8b;
	cp->lap[2] = 0x9e;

	/*
	 * Calculate inquire length in 1.28 second units
	 * v2.x specification says that 1.28 -> 61.44 seconds
	 * range is acceptable
	 */

	if (length <= 0)
		length = 5;
	else if (length == 1)
		length = 2;
	else if (length > 62)
		length = 62;

	cp->inquiry_length = (uint8_t)((length * 100) / 128);

	if (num_rsp <= 0 || num_rsp > 255)
		num_rsp = 8;
	cp->num_responses = (uint8_t) num_rsp;

	i = *ii = calloc(num_rsp, sizeof(struct bt_devinquiry));
	if (i == NULL) {
		bt_devclose(s);
		errno = ENOMEM;
		return (-1);
	}

	if (bt_devsend(s,
		NG_HCI_OPCODE(NG_HCI_OGF_LINK_CONTROL, NG_HCI_OCF_INQUIRY),
			cp, sizeof(*cp)) < 0) {
		free(i);
		bt_devclose(s);
		return (-1);
	}

wait_for_more:

	n = bt_devrecv(s, buf, sizeof(buf), length);
	if (n < 0) {
		free(i);
		bt_devclose(s);
		return (-1);
	}

	if (n < sizeof(ng_hci_event_pkt_t)) {
		free(i);
		bt_devclose(s);
		errno = EIO;
		return (-1);
	}

	switch (e->event) {
	case NG_HCI_EVENT_INQUIRY_COMPL:
		break;

	case NG_HCI_EVENT_INQUIRY_RESULT:
		ir = (ng_hci_inquiry_response *)(ep + 1);

		for (n = 0; n < MIN(ep->num_responses, num_rsp); n ++) {
			bdaddr_copy(&i->bdaddr, &ir->bdaddr);
			i->pscan_rep_mode = ir->page_scan_rep_mode;
			i->pscan_period_mode = ir->page_scan_period_mode;
			memcpy(i->dev_class, ir->uclass, sizeof(i->dev_class));
			i->clock_offset = le16toh(ir->clock_offset);

			ir ++;
			i ++;
			num_rsp --;
		}
		/* FALLTHROUGH */

	default:
		goto wait_for_more;
		/* NOT REACHED */
	}

	bt_devclose(s);
		
	return (i - *ii);
}
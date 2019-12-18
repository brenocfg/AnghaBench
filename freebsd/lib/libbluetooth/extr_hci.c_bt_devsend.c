#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct iovec {int iov_len; TYPE_1__* iov_base; } ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/  opcode; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ng_hci_cmd_pkt_t ;
typedef  int /*<<< orphan*/  h ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  NG_HCI_CMD_PKT ; 
 size_t UINT8_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 scalar_t__ writev (int,struct iovec*,int) ; 

int
bt_devsend(int s, uint16_t opcode, void *param, size_t plen)
{
	ng_hci_cmd_pkt_t	h;
	struct iovec		iv[2];
	int			ivn;

	if ((plen == 0 && param != NULL) ||
	    (plen > 0 && param == NULL) ||
	    plen > UINT8_MAX) { 
		errno = EINVAL;
		return (-1);
	}

	iv[0].iov_base = &h;
	iv[0].iov_len = sizeof(h);
	ivn = 1;

	h.type = NG_HCI_CMD_PKT;
	h.opcode = htole16(opcode);
	if (plen > 0) {
		h.length = plen;

		iv[1].iov_base = param;
		iv[1].iov_len = plen;
		ivn = 2;
	} else
		h.length = 0;

	while (writev(s, iv, ivn) < 0) {
		if (errno == EAGAIN || errno == EINTR)
			continue;

		return (-1);
	}

	return (0);
}
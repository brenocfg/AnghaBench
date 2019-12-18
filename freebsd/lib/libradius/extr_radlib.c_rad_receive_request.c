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
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct rad_handle {scalar_t__ type; int srv; int in_len; int* in; int num_servers; int /*<<< orphan*/  in_pos; TYPE_4__* servers; int /*<<< orphan*/  fd; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct TYPE_8__ {TYPE_3__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGSIZE ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  POS_ATTRS ; 
 size_t POS_CODE ; 
 size_t POS_LENGTH ; 
 scalar_t__ RADIUS_SERVER ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*,...) ; 
 scalar_t__ is_valid_request (struct rad_handle*) ; 
 int recvfrom (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
rad_receive_request(struct rad_handle *h)
{
	struct sockaddr_in from;
	socklen_t fromlen;
	int n;

	if (h->type != RADIUS_SERVER) {
		generr(h, "denied function call");
		return (-1);
	}
	h->srv = -1;
	fromlen = sizeof(from);
	h->in_len = recvfrom(h->fd, h->in,
	    MSGSIZE, MSG_WAITALL, (struct sockaddr *)&from, &fromlen);
	if (h->in_len == -1) {
		generr(h, "recvfrom: %s", strerror(errno));
		return (-1);
	}
	for (n = 0; n < h->num_servers; n++) {
		if (h->servers[n].addr.sin_addr.s_addr == from.sin_addr.s_addr) {
			h->servers[n].addr.sin_port = from.sin_port;
			h->srv = n;
			break;
		}
	}
	if (h->srv == -1)
		return (-2);
	if (is_valid_request(h)) {
		h->in_len = h->in[POS_LENGTH] << 8 |
		    h->in[POS_LENGTH+1];
		h->in_pos = POS_ATTRS;
		return (h->in[POS_CODE]);
	}
	return (-3);
}
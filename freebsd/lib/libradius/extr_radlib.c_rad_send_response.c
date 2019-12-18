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
struct sockaddr {int dummy; } ;
struct rad_handle {scalar_t__ type; int* out; int out_len; scalar_t__* in; size_t srv; TYPE_1__* servers; int /*<<< orphan*/  fd; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 size_t POS_CODE ; 
 size_t POS_LENGTH ; 
 scalar_t__ RADIUS_SERVER ; 
 scalar_t__ RAD_ACCESS_REQUEST ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*,...) ; 
 int /*<<< orphan*/  insert_message_authenticator (struct rad_handle*,int) ; 
 int /*<<< orphan*/  insert_request_authenticator (struct rad_handle*,int) ; 
 int sendto (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
rad_send_response(struct rad_handle *h)
{
	int n;

	if (h->type != RADIUS_SERVER) {
		generr(h, "denied function call");
		return (-1);
	}
	/* Fill in the length field in the message */
	h->out[POS_LENGTH] = h->out_len >> 8;
	h->out[POS_LENGTH+1] = h->out_len;

	insert_message_authenticator(h,
	    (h->in[POS_CODE] == RAD_ACCESS_REQUEST) ? 1 : 0);
	insert_request_authenticator(h, 1);

	/* Send the request */
	n = sendto(h->fd, h->out, h->out_len, 0,
	    (const struct sockaddr *)&h->servers[h->srv].addr,
	    sizeof h->servers[h->srv].addr);
	if (n != h->out_len) {
		if (n == -1)
			generr(h, "sendto: %s", strerror(errno));
		else
			generr(h, "sendto: short write");
		return -1;
	}

	return 0;
}
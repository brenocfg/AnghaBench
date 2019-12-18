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
typedef  int /*<<< orphan*/  u8 ;
struct radius_msg {int /*<<< orphan*/ * buf; int /*<<< orphan*/  hdr; } ;
struct radius_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_DEFAULT_MSG_SIZE ; 
 struct radius_msg* os_zalloc (int) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 scalar_t__ radius_msg_initialize (struct radius_msg*) ; 
 int /*<<< orphan*/  radius_msg_set_hdr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put (int /*<<< orphan*/ *,int) ; 

struct radius_msg * radius_msg_new(u8 code, u8 identifier)
{
	struct radius_msg *msg;

	msg = os_zalloc(sizeof(*msg));
	if (msg == NULL)
		return NULL;

	msg->buf = wpabuf_alloc(RADIUS_DEFAULT_MSG_SIZE);
	if (msg->buf == NULL || radius_msg_initialize(msg)) {
		radius_msg_free(msg);
		return NULL;
	}
	msg->hdr = wpabuf_put(msg->buf, sizeof(struct radius_hdr));

	radius_msg_set_hdr(msg, code, identifier);

	return msg;
}
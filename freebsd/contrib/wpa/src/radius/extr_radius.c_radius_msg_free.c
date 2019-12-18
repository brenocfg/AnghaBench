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
struct radius_msg {struct radius_msg* attr_pos; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct radius_msg*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void radius_msg_free(struct radius_msg *msg)
{
	if (msg == NULL)
		return;

	wpabuf_free(msg->buf);
	os_free(msg->attr_pos);
	os_free(msg);
}
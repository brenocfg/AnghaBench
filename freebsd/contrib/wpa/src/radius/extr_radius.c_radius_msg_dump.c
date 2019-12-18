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
struct radius_msg {size_t attr_used; TYPE_1__* hdr; } ;
struct radius_attr_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  identifier; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_code_string (int /*<<< orphan*/ ) ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 
 int /*<<< orphan*/  radius_msg_dump_attr (struct radius_attr_hdr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radius_msg_dump(struct radius_msg *msg)
{
	size_t i;

	wpa_printf(MSG_INFO, "RADIUS message: code=%d (%s) identifier=%d length=%d",
		   msg->hdr->code, radius_code_string(msg->hdr->code),
		   msg->hdr->identifier, be_to_host16(msg->hdr->length));

	for (i = 0; i < msg->attr_used; i++) {
		struct radius_attr_hdr *attr = radius_get_attr_hdr(msg, i);
		radius_msg_dump_attr(attr);
	}
}
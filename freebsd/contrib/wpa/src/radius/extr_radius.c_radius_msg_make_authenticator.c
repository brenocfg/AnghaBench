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
typedef  int /*<<< orphan*/  u8 ;
struct radius_msg {TYPE_1__* hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  authenticator; } ;

/* Variables and functions */
 int os_get_random (int /*<<< orphan*/ *,int) ; 

int radius_msg_make_authenticator(struct radius_msg *msg)
{
	return os_get_random((u8 *) &msg->hdr->authenticator,
			     sizeof(msg->hdr->authenticator));
}
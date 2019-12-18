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
typedef  int /*<<< orphan*/  uint32_t ;
struct xsd_sockmsg {scalar_t__ len; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  request_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ xs ; 
 int xs_read_reply (int /*<<< orphan*/ *,scalar_t__*,void**) ; 
 int xs_write_store (struct xsd_sockmsg*,scalar_t__) ; 

int
xs_dev_request_and_reply(struct xsd_sockmsg *msg, void **result)
{
	uint32_t request_type;
	int error;

	request_type = msg->type;

	sx_xlock(&xs.request_mutex);
	if ((error = xs_write_store(msg, sizeof(*msg) + msg->len)) == 0)
		error = xs_read_reply(&msg->type, &msg->len, result);
	sx_xunlock(&xs.request_mutex);

	return (error);
}
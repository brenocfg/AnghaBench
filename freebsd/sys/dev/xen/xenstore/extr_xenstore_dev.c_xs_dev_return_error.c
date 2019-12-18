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
struct xsd_sockmsg {int req_id; int tx_id; int len; int /*<<< orphan*/  type; } ;
struct xs_dev_data {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XS_ERROR ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* xs_dev_error_to_string (int) ; 
 int /*<<< orphan*/  xs_queue_reply (struct xs_dev_data*,char const*,int) ; 

__attribute__((used)) static void
xs_dev_return_error(struct xs_dev_data *u, int error, int req_id, int tx_id)
{
	struct xsd_sockmsg msg;
	const char *payload;

	msg.type = XS_ERROR;
	msg.req_id = req_id;
	msg.tx_id = tx_id;
	payload = NULL;


	payload = xs_dev_error_to_string(error);
	if (payload == NULL)
		payload = xs_dev_error_to_string(EINVAL);
	KASSERT(payload != NULL, ("Unable to find string for EINVAL errno"));

	msg.len = strlen(payload) + 1;

	mtx_lock(&u->lock);
	xs_queue_reply(u, (char *)&msg, sizeof(msg));
	xs_queue_reply(u, payload, msg.len);
	mtx_unlock(&u->lock);
}
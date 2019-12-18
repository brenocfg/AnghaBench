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
struct xsd_sockmsg {size_t len; scalar_t__ tx_id; scalar_t__ req_id; int /*<<< orphan*/  type; } ;
struct xs_watch {scalar_t__ callback_data; } ;
struct xs_dev_watch {char const* token; TYPE_1__* user; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XS_WATCH_EVENT ; 
 size_t XS_WATCH_PATH ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  xs_queue_reply (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void
xs_dev_watch_cb(struct xs_watch *watch, const char **vec, unsigned int len)
{
	struct xs_dev_watch *dwatch;
	struct xsd_sockmsg msg;
	char *payload;

	dwatch = (struct xs_dev_watch *)watch->callback_data;
	msg.type = XS_WATCH_EVENT;
	msg.req_id = msg.tx_id = 0;
	msg.len = strlen(vec[XS_WATCH_PATH]) + strlen(dwatch->token) + 2;

	payload = malloc(msg.len, M_XENSTORE, M_WAITOK);
	strcpy(payload, vec[XS_WATCH_PATH]);
	strcpy(&payload[strlen(vec[XS_WATCH_PATH]) + 1], dwatch->token);
	mtx_lock(&dwatch->user->lock);
	xs_queue_reply(dwatch->user, (char *)&msg, sizeof(msg));
	xs_queue_reply(dwatch->user, payload, msg.len);
	mtx_unlock(&dwatch->user->lock);
	free(payload, M_XENSTORE);
}
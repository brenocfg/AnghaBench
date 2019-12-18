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
struct sockaddr {int dummy; } ;
struct radius_session {void* eap; int /*<<< orphan*/  last_from_port; int /*<<< orphan*/  last_from_addr; int /*<<< orphan*/  last_fromlen; int /*<<< orphan*/  last_from; struct radius_msg* last_msg; struct radius_session* next; } ;
struct radius_server_data {struct radius_client* clients; } ;
struct radius_msg {int dummy; } ;
struct radius_client {struct radius_session* sessions; struct radius_client* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_DEBUG (char*) ; 
 int /*<<< orphan*/  eap_sm_pending_cb (void*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 int radius_server_request (struct radius_server_data*,struct radius_msg*,struct sockaddr*,int /*<<< orphan*/ ,struct radius_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radius_session*) ; 

void radius_server_eap_pending_cb(struct radius_server_data *data, void *ctx)
{
	struct radius_client *cli;
	struct radius_session *s, *sess = NULL;
	struct radius_msg *msg;

	if (data == NULL)
		return;

	for (cli = data->clients; cli; cli = cli->next) {
		for (s = cli->sessions; s; s = s->next) {
			if (s->eap == ctx && s->last_msg) {
				sess = s;
				break;
			}
		}
		if (sess)
			break;
	}

	if (sess == NULL) {
		RADIUS_DEBUG("No session matched callback ctx");
		return;
	}

	msg = sess->last_msg;
	sess->last_msg = NULL;
	eap_sm_pending_cb(sess->eap);
	if (radius_server_request(data, msg,
				  (struct sockaddr *) &sess->last_from,
				  sess->last_fromlen, cli,
				  sess->last_from_addr,
				  sess->last_from_port, sess) == -2)
		return; /* msg was stored with the session */

	radius_msg_free(msg);
}
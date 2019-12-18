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
struct radius_session {struct radius_session* next; struct radius_client* client; } ;
struct radius_server_data {int dummy; } ;
struct radius_client {struct radius_session* sessions; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct radius_server_data*,struct radius_session*) ; 
 int /*<<< orphan*/  radius_server_session_free (struct radius_server_data*,struct radius_session*) ; 
 int /*<<< orphan*/  radius_server_session_remove_timeout ; 

__attribute__((used)) static void radius_server_session_remove(struct radius_server_data *data,
					 struct radius_session *sess)
{
	struct radius_client *client = sess->client;
	struct radius_session *session, *prev;

	eloop_cancel_timeout(radius_server_session_remove_timeout, data, sess);

	prev = NULL;
	session = client->sessions;
	while (session) {
		if (session == sess) {
			if (prev == NULL) {
				client->sessions = sess->next;
			} else {
				prev->next = sess->next;
			}
			radius_server_session_free(data, sess);
			break;
		}
		prev = session;
		session = session->next;
	}
}
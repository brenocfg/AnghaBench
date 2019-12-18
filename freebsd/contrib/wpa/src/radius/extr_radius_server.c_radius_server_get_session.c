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
struct radius_session {unsigned int sess_id; struct radius_session* next; } ;
struct radius_client {struct radius_session* sessions; } ;

/* Variables and functions */

__attribute__((used)) static struct radius_session *
radius_server_get_session(struct radius_client *client, unsigned int sess_id)
{
	struct radius_session *sess = client->sessions;

	while (sess) {
		if (sess->sess_id == sess_id) {
			break;
		}
		sess = sess->next;
	}

	return sess;
}
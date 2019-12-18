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
struct radius_session {struct radius_session* next; } ;
struct radius_server_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radius_server_session_free (struct radius_server_data*,struct radius_session*) ; 

__attribute__((used)) static void radius_server_free_sessions(struct radius_server_data *data,
					struct radius_session *sessions)
{
	struct radius_session *session, *prev;

	session = sessions;
	while (session) {
		prev = session;
		session = session->next;
		radius_server_session_free(data, prev);
	}
}
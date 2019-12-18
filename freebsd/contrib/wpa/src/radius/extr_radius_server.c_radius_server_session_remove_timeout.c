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
struct radius_session {int /*<<< orphan*/  sess_id; } ;
struct radius_server_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_server_session_remove (struct radius_server_data*,struct radius_session*) ; 

__attribute__((used)) static void radius_server_session_remove_timeout(void *eloop_ctx,
						 void *timeout_ctx)
{
	struct radius_server_data *data = eloop_ctx;
	struct radius_session *sess = timeout_ctx;
	RADIUS_DEBUG("Removing completed session 0x%x", sess->sess_id);
	radius_server_session_remove(data, sess);
}
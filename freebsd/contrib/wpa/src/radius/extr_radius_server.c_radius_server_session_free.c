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
struct radius_session {struct radius_session* nas_ip; struct radius_session* username; int /*<<< orphan*/  last_reply; struct radius_session* last_from_addr; int /*<<< orphan*/  last_msg; int /*<<< orphan*/  eap; } ;
struct radius_server_data {int /*<<< orphan*/  num_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_server_sm_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct radius_server_data*,struct radius_session*) ; 
 int /*<<< orphan*/  os_free (struct radius_session*) ; 
 int /*<<< orphan*/  radius_msg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_server_session_remove_timeout ; 
 int /*<<< orphan*/  radius_server_session_timeout ; 

__attribute__((used)) static void radius_server_session_free(struct radius_server_data *data,
				       struct radius_session *sess)
{
	eloop_cancel_timeout(radius_server_session_timeout, data, sess);
	eloop_cancel_timeout(radius_server_session_remove_timeout, data, sess);
	eap_server_sm_deinit(sess->eap);
	radius_msg_free(sess->last_msg);
	os_free(sess->last_from_addr);
	radius_msg_free(sess->last_reply);
	os_free(sess->username);
	os_free(sess->nas_ip);
	os_free(sess);
	data->num_sess--;
}
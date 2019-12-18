#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct radius_msg {int dummy; } ;
struct radius_client_data {scalar_t__ acct_sock; scalar_t__ auth_sock; int /*<<< orphan*/  ctx; struct hostapd_radius_servers* conf; } ;
struct hostapd_radius_servers {scalar_t__ msg_dumps; TYPE_2__* auth_server; TYPE_1__* acct_server; } ;
struct TYPE_4__ {size_t shared_secret_len; int /*<<< orphan*/  requests; int /*<<< orphan*/ * shared_secret; } ;
struct TYPE_3__ {size_t shared_secret_len; int /*<<< orphan*/  requests; int /*<<< orphan*/ * shared_secret; } ;
typedef  int /*<<< orphan*/  RadiusType ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  RADIUS_ACCT ; 
 int /*<<< orphan*/  RADIUS_ACCT_INTERIM ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  radius_client_handle_send_error (struct radius_client_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_client_init_acct (struct radius_client_data*) ; 
 int /*<<< orphan*/  radius_client_init_auth (struct radius_client_data*) ; 
 int /*<<< orphan*/  radius_client_list_add (struct radius_client_data*,struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  radius_msg_dump (struct radius_msg*) ; 
 int /*<<< orphan*/  radius_msg_finish (struct radius_msg*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  radius_msg_finish_acct (struct radius_msg*,int /*<<< orphan*/  const*,size_t) ; 
 struct wpabuf* radius_msg_get_buf (struct radius_msg*) ; 
 int send (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

int radius_client_send(struct radius_client_data *radius,
		       struct radius_msg *msg, RadiusType msg_type,
		       const u8 *addr)
{
	struct hostapd_radius_servers *conf = radius->conf;
	const u8 *shared_secret;
	size_t shared_secret_len;
	char *name;
	int s, res;
	struct wpabuf *buf;

	if (msg_type == RADIUS_ACCT || msg_type == RADIUS_ACCT_INTERIM) {
		if (conf->acct_server && radius->acct_sock < 0)
			radius_client_init_acct(radius);

		if (conf->acct_server == NULL || radius->acct_sock < 0 ||
		    conf->acct_server->shared_secret == NULL) {
			hostapd_logger(radius->ctx, NULL,
				       HOSTAPD_MODULE_RADIUS,
				       HOSTAPD_LEVEL_INFO,
				       "No accounting server configured");
			return -1;
		}
		shared_secret = conf->acct_server->shared_secret;
		shared_secret_len = conf->acct_server->shared_secret_len;
		radius_msg_finish_acct(msg, shared_secret, shared_secret_len);
		name = "accounting";
		s = radius->acct_sock;
		conf->acct_server->requests++;
	} else {
		if (conf->auth_server && radius->auth_sock < 0)
			radius_client_init_auth(radius);

		if (conf->auth_server == NULL || radius->auth_sock < 0 ||
		    conf->auth_server->shared_secret == NULL) {
			hostapd_logger(radius->ctx, NULL,
				       HOSTAPD_MODULE_RADIUS,
				       HOSTAPD_LEVEL_INFO,
				       "No authentication server configured");
			return -1;
		}
		shared_secret = conf->auth_server->shared_secret;
		shared_secret_len = conf->auth_server->shared_secret_len;
		radius_msg_finish(msg, shared_secret, shared_secret_len);
		name = "authentication";
		s = radius->auth_sock;
		conf->auth_server->requests++;
	}

	hostapd_logger(radius->ctx, NULL, HOSTAPD_MODULE_RADIUS,
		       HOSTAPD_LEVEL_DEBUG, "Sending RADIUS message to %s "
		       "server", name);
	if (conf->msg_dumps)
		radius_msg_dump(msg);

	buf = radius_msg_get_buf(msg);
	res = send(s, wpabuf_head(buf), wpabuf_len(buf), 0);
	if (res < 0)
		radius_client_handle_send_error(radius, s, msg_type);

	radius_client_list_add(radius, msg, msg_type, shared_secret,
			       shared_secret_len, addr);

	return 0;
}
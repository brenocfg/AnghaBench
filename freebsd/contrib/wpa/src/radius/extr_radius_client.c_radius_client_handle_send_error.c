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
struct radius_client_data {int /*<<< orphan*/  ctx; } ;
typedef  scalar_t__ RadiusType ;

/* Variables and functions */
 int EACCES ; 
 int EBADF ; 
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ RADIUS_ACCT ; 
 scalar_t__ RADIUS_ACCT_INTERIM ; 
 int errno ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  radius_client_init_acct (struct radius_client_data*) ; 
 int /*<<< orphan*/  radius_client_init_auth (struct radius_client_data*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radius_client_handle_send_error(struct radius_client_data *radius,
					   int s, RadiusType msg_type)
{
#ifndef CONFIG_NATIVE_WINDOWS
	int _errno = errno;
	wpa_printf(MSG_INFO, "send[RADIUS,s=%d]: %s", s, strerror(errno));
	if (_errno == ENOTCONN || _errno == EDESTADDRREQ || _errno == EINVAL ||
	    _errno == EBADF || _errno == ENETUNREACH || _errno == EACCES) {
		hostapd_logger(radius->ctx, NULL, HOSTAPD_MODULE_RADIUS,
			       HOSTAPD_LEVEL_INFO,
			       "Send failed - maybe interface status changed -"
			       " try to connect again");
		if (msg_type == RADIUS_ACCT ||
		    msg_type == RADIUS_ACCT_INTERIM) {
			radius_client_init_acct(radius);
			return 0;
		} else {
			radius_client_init_auth(radius);
			return 1;
		}
	}
#endif /* CONFIG_NATIVE_WINDOWS */

	return 0;
}
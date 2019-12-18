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
struct radius_client_data {struct radius_client_data* acct_handlers; struct radius_client_data* auth_handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct radius_client_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct radius_client_data*) ; 
 int /*<<< orphan*/  radius_client_flush (struct radius_client_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_close_acct_sockets (struct radius_client_data*) ; 
 int /*<<< orphan*/  radius_close_auth_sockets (struct radius_client_data*) ; 
 int /*<<< orphan*/  radius_retry_primary_timer ; 

void radius_client_deinit(struct radius_client_data *radius)
{
	if (!radius)
		return;

	radius_close_auth_sockets(radius);
	radius_close_acct_sockets(radius);

	eloop_cancel_timeout(radius_retry_primary_timer, radius, NULL);

	radius_client_flush(radius, 0);
	os_free(radius->auth_handlers);
	os_free(radius->acct_handlers);
	os_free(radius);
}
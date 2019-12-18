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
struct radius_das_data {scalar_t__ sock; int /*<<< orphan*/  shared_secret_len; int /*<<< orphan*/ * shared_secret; int /*<<< orphan*/  client_addr; int /*<<< orphan*/  coa; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  ctx; int /*<<< orphan*/  require_message_authenticator; int /*<<< orphan*/  require_event_timestamp; int /*<<< orphan*/  time_window; } ;
struct radius_das_conf {scalar_t__ port; int /*<<< orphan*/  shared_secret_len; int /*<<< orphan*/ * shared_secret; int /*<<< orphan*/ * client_addr; int /*<<< orphan*/  coa; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  ctx; int /*<<< orphan*/  require_message_authenticator; int /*<<< orphan*/  require_event_timestamp; int /*<<< orphan*/  time_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ eloop_register_read_sock (scalar_t__,int /*<<< orphan*/ ,struct radius_das_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct radius_das_data* os_zalloc (int) ; 
 int /*<<< orphan*/  radius_das_deinit (struct radius_das_data*) ; 
 scalar_t__ radius_das_open_socket (scalar_t__) ; 
 int /*<<< orphan*/  radius_das_receive ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct radius_das_data *
radius_das_init(struct radius_das_conf *conf)
{
	struct radius_das_data *das;

	if (conf->port == 0 || conf->shared_secret == NULL ||
	    conf->client_addr == NULL)
		return NULL;

	das = os_zalloc(sizeof(*das));
	if (das == NULL)
		return NULL;

	das->time_window = conf->time_window;
	das->require_event_timestamp = conf->require_event_timestamp;
	das->require_message_authenticator =
		conf->require_message_authenticator;
	das->ctx = conf->ctx;
	das->disconnect = conf->disconnect;
	das->coa = conf->coa;

	os_memcpy(&das->client_addr, conf->client_addr,
		  sizeof(das->client_addr));

	das->shared_secret = os_memdup(conf->shared_secret,
				       conf->shared_secret_len);
	if (das->shared_secret == NULL) {
		radius_das_deinit(das);
		return NULL;
	}
	das->shared_secret_len = conf->shared_secret_len;

	das->sock = radius_das_open_socket(conf->port);
	if (das->sock < 0) {
		wpa_printf(MSG_ERROR, "Failed to open UDP socket for RADIUS "
			   "DAS");
		radius_das_deinit(das);
		return NULL;
	}

	if (eloop_register_read_sock(das->sock, radius_das_receive, das, NULL))
	{
		radius_das_deinit(das);
		return NULL;
	}

	return das;
}
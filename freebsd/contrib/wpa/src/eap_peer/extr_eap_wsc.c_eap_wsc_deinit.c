#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eap_wsc_data {TYPE_1__* wps_ctx; int /*<<< orphan*/  wps; int /*<<< orphan*/  out_buf; int /*<<< orphan*/  in_buf; } ;
struct eap_sm {int dummy; } ;
struct TYPE_2__ {struct eap_wsc_data* network_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct eap_wsc_data*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_deinit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_wsc_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_wsc_data *data = priv;
	wpabuf_free(data->in_buf);
	wpabuf_free(data->out_buf);
	wps_deinit(data->wps);
	os_free(data->wps_ctx->network_key);
	data->wps_ctx->network_key = NULL;
	os_free(data);
}
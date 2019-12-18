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
struct eap_wsc_data {int /*<<< orphan*/  wps; int /*<<< orphan*/  out_buf; int /*<<< orphan*/  in_buf; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_wsc_ext_reg_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct eap_sm*,struct eap_wsc_data*) ; 
 int /*<<< orphan*/  os_free (struct eap_wsc_data*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_deinit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_wsc_reset(struct eap_sm *sm, void *priv)
{
	struct eap_wsc_data *data = priv;
	eloop_cancel_timeout(eap_wsc_ext_reg_timeout, sm, data);
	wpabuf_free(data->in_buf);
	wpabuf_free(data->out_buf);
	wps_deinit(data->wps);
	os_free(data);
}
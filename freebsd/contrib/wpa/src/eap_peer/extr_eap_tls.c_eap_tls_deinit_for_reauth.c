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
struct eap_tls_data {int /*<<< orphan*/ * pending_resp; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_tls_deinit_for_reauth(struct eap_sm *sm, void *priv)
{
	struct eap_tls_data *data = priv;

	wpabuf_free(data->pending_resp);
	data->pending_resp = NULL;
}
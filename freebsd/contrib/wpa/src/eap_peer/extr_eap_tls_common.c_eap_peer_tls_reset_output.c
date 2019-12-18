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
struct eap_ssl_data {int /*<<< orphan*/ * tls_out; scalar_t__ tls_out_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void eap_peer_tls_reset_output(struct eap_ssl_data *data)
{
	data->tls_out_pos = 0;
	wpabuf_free(data->tls_out);
	data->tls_out = NULL;
}
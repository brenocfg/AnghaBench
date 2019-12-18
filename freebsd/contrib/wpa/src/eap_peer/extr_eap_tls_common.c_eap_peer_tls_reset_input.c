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
struct eap_ssl_data {int /*<<< orphan*/ * tls_in; scalar_t__ tls_in_total; scalar_t__ tls_in_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void eap_peer_tls_reset_input(struct eap_ssl_data *data)
{
	data->tls_in_left = data->tls_in_total = 0;
	wpabuf_free(data->tls_in);
	data->tls_in = NULL;
}
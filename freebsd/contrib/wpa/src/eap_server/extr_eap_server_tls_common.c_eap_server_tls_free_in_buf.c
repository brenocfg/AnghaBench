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
struct eap_ssl_data {int /*<<< orphan*/ * tls_in; int /*<<< orphan*/  tmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_server_tls_free_in_buf(struct eap_ssl_data *data)
{
	if (data->tls_in != &data->tmpbuf)
		wpabuf_free(data->tls_in);
	data->tls_in = NULL;
}
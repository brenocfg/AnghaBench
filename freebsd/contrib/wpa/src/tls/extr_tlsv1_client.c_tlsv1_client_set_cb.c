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
struct tlsv1_client {void (* event_cb ) (void*,int,union tls_event_data*) ;int cert_in_cb; void* cb_ctx; } ;

/* Variables and functions */

void tlsv1_client_set_cb(struct tlsv1_client *conn,
			 void (*event_cb)(void *ctx, enum tls_event ev,
					  union tls_event_data *data),
			 void *cb_ctx,
			 int cert_in_cb)
{
	conn->event_cb = event_cb;
	conn->cb_ctx = cb_ctx;
	conn->cert_in_cb = !!cert_in_cb;
}
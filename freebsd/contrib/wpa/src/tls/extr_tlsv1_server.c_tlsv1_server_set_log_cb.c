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
struct tlsv1_server {void (* log_cb ) (void*,char const*) ;void* log_cb_ctx; } ;

/* Variables and functions */

void tlsv1_server_set_log_cb(struct tlsv1_server *conn,
			     void (*cb)(void *ctx, const char *msg), void *ctx)
{
	conn->log_cb = cb;
	conn->log_cb_ctx = ctx;
}
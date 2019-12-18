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
typedef  int /*<<< orphan*/  tlsv1_client_session_ticket_cb ;
struct tlsv1_client {void* session_ticket_cb_ctx; int /*<<< orphan*/  session_ticket_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 

void tlsv1_client_set_session_ticket_cb(struct tlsv1_client *conn,
					tlsv1_client_session_ticket_cb cb,
					void *ctx)
{
	wpa_printf(MSG_DEBUG, "TLSv1: SessionTicket callback set %p (ctx %p)",
		   cb, ctx);
	conn->session_ticket_cb = cb;
	conn->session_ticket_cb_ctx = ctx;
}
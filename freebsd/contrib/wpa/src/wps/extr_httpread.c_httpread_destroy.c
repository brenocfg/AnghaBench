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
struct httpread {int sd; struct httpread* uri; struct httpread* body; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct httpread*) ; 
 int /*<<< orphan*/  eloop_unregister_sock (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpread_timeout_handler ; 
 int /*<<< orphan*/  os_free (struct httpread*) ; 
 int /*<<< orphan*/  os_memset (struct httpread*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct httpread*) ; 

void httpread_destroy(struct httpread *h)
{
	wpa_printf(MSG_DEBUG, "httpread_destroy(%p)", h);
	if (!h)
		return;

	eloop_cancel_timeout(httpread_timeout_handler, NULL, h);
	eloop_unregister_sock(h->sd, EVENT_TYPE_READ);
	os_free(h->body);
	os_free(h->uri);
	os_memset(h, 0, sizeof(*h));  /* aid debugging */
	h->sd = -1;     /* aid debugging */
	os_free(h);
}
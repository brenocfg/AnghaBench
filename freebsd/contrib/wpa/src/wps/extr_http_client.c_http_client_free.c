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
struct http_client {scalar_t__ sd; int /*<<< orphan*/  req; int /*<<< orphan*/  hread; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_WRITE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct http_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_unregister_sock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_client_timeout ; 
 int /*<<< orphan*/  httpread_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct http_client*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void http_client_free(struct http_client *c)
{
	if (c == NULL)
		return;
	httpread_destroy(c->hread);
	wpabuf_free(c->req);
	if (c->sd >= 0) {
		eloop_unregister_sock(c->sd, EVENT_TYPE_WRITE);
		close(c->sd);
	}
	eloop_cancel_timeout(http_client_timeout, c, NULL);
	os_free(c);
}
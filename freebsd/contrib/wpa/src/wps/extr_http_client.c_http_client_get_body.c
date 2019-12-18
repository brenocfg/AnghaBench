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
struct wpabuf {int dummy; } ;
struct http_client {struct wpabuf body; int /*<<< orphan*/ * hread; } ;

/* Variables and functions */
 int /*<<< orphan*/  httpread_data_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpread_length_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct wpabuf * http_client_get_body(struct http_client *c)
{
	if (c->hread == NULL)
		return NULL;
	wpabuf_set(&c->body, httpread_data_get(c->hread),
		   httpread_length_get(c->hread));
	return &c->body;
}
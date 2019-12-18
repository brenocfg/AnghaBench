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
struct http_client {int /*<<< orphan*/ * hread; } ;

/* Variables and functions */
 char* httpread_hdr_line_get (int /*<<< orphan*/ *,char const*) ; 

char * http_client_get_hdr_line(struct http_client *c, const char *tag)
{
	if (c->hread == NULL)
		return NULL;
	return httpread_hdr_line_get(c->hread, tag);
}
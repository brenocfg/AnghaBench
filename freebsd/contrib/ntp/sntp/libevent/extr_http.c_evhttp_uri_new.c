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
struct evhttp_uri {int port; } ;

/* Variables and functions */
 struct evhttp_uri* mm_calloc (int,int) ; 

struct evhttp_uri *
evhttp_uri_new(void)
{
	struct evhttp_uri *uri = mm_calloc(sizeof(struct evhttp_uri), 1);
	if (uri)
		uri->port = -1;
	return uri;
}
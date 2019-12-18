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

int
evhttp_uri_set_port(struct evhttp_uri *uri, int port)
{
	if (port < -1)
		return -1;
	uri->port = port;
	return 0;
}
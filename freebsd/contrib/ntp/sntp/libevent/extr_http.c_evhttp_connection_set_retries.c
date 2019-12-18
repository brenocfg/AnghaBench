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
struct evhttp_connection {int retry_max; } ;

/* Variables and functions */

void
evhttp_connection_set_retries(struct evhttp_connection *evcon,
    int retry_max)
{
	evcon->retry_max = retry_max;
}
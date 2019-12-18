#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evrpc_request_wrapper {TYPE_1__* hook_meta; } ;
struct evhttp_connection {int dummy; } ;
struct TYPE_2__ {struct evhttp_connection* evcon; } ;

/* Variables and functions */

struct evhttp_connection *
evrpc_hook_get_connection(void *ctx)
{
	struct evrpc_request_wrapper *req = ctx;
	return (req->hook_meta != NULL ? req->hook_meta->evcon : NULL);
}
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
struct evrpc_request_wrapper {struct evrpc_pool* pool; } ;
struct evrpc_pool {int dummy; } ;

/* Variables and functions */

struct evrpc_pool *
evrpc_request_get_pool(struct evrpc_request_wrapper *ctx)
{
	return (ctx->pool);
}
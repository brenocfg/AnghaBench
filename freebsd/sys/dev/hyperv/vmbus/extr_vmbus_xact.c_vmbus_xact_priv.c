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
struct vmbus_xact {void* x_priv; TYPE_1__* x_ctx; } ;
struct TYPE_2__ {size_t xc_priv_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,size_t) ; 

void *
vmbus_xact_priv(const struct vmbus_xact *xact, size_t priv_len)
{

	if (priv_len > xact->x_ctx->xc_priv_size)
		panic("invalid priv size %zu", priv_len);
	return (xact->x_priv);
}
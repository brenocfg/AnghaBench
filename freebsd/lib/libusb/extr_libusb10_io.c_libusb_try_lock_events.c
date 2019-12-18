#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ctx_handler; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 int CTX_TRYLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  CTX_UNLOCK (TYPE_1__*) ; 
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 
 scalar_t__ NO_THREAD ; 
 scalar_t__ pthread_self () ; 

int
libusb_try_lock_events(libusb_context *ctx)
{
	int err;

	ctx = GET_CONTEXT(ctx);
	if (ctx == NULL)
		return (1);

	err = CTX_TRYLOCK(ctx);
	if (err)
		return (1);

	err = (ctx->ctx_handler != NO_THREAD);
	if (err)
		CTX_UNLOCK(ctx);
	else
		ctx->ctx_handler = pthread_self();

	return (err);
}
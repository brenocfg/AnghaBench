#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pthread_t ;
struct TYPE_10__ {scalar_t__ hotplug_handler; int /*<<< orphan*/  ctx_cond; int /*<<< orphan*/  hotplug_lock; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/ * ctrl_pipe; int /*<<< orphan*/  ctx_poll; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  HOTPLUG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  HOTPLUG_UNLOCK (TYPE_1__*) ; 
 scalar_t__ NO_THREAD ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_context_lock ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libusb10_remove_pollfd (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (scalar_t__,void**) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* usbi_default_context ; 

void
libusb_exit(libusb_context *ctx)
{
	ctx = GET_CONTEXT(ctx);

	if (ctx == NULL)
		return;

	/* stop hotplug thread, if any */

	if (ctx->hotplug_handler != NO_THREAD) {
		pthread_t td;
		void *ptr;

		HOTPLUG_LOCK(ctx);
		td = ctx->hotplug_handler;
		ctx->hotplug_handler = NO_THREAD;
		HOTPLUG_UNLOCK(ctx);

		pthread_join(td, &ptr);
	}

	/* XXX cleanup devices */

	libusb10_remove_pollfd(ctx, &ctx->ctx_poll);
	close(ctx->ctrl_pipe[0]);
	close(ctx->ctrl_pipe[1]);
	pthread_mutex_destroy(&ctx->ctx_lock);
	pthread_mutex_destroy(&ctx->hotplug_lock);
	pthread_cond_destroy(&ctx->ctx_cond);

	pthread_mutex_lock(&default_context_lock);
	if (ctx == usbi_default_context) {
		usbi_default_context = NULL;
	}
	pthread_mutex_unlock(&default_context_lock);

	free(ctx);
}
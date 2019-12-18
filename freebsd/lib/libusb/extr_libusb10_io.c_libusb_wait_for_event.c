#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ ctx_handler; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_cond; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DPRINTF (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int ETIMEDOUT ; 
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int LIBUSB_ERROR_OTHER ; 
 scalar_t__ NO_THREAD ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* pthread_self () ; 

int
libusb_wait_for_event(libusb_context *ctx, struct timeval *tv)
{
	struct timespec ts;
	int err;

	ctx = GET_CONTEXT(ctx);
	DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "libusb_wait_for_event enter");

	if (tv == NULL) {
		pthread_cond_wait(&ctx->ctx_cond,
		    &ctx->ctx_lock);
		/* try to grab polling of actual events, if any */
		if (ctx->ctx_handler == NO_THREAD)
			ctx->ctx_handler = pthread_self();
		return (0);
	}
	err = clock_gettime(CLOCK_MONOTONIC, &ts);
	if (err < 0)
		return (LIBUSB_ERROR_OTHER);

	/*
	 * The "tv" arguments points to a relative time structure and
	 * not an absolute time structure.
	 */
	ts.tv_sec += tv->tv_sec;
	ts.tv_nsec += tv->tv_usec * 1000;
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}
	err = pthread_cond_timedwait(&ctx->ctx_cond,
	    &ctx->ctx_lock, &ts);
	/* try to grab polling of actual events, if any */
	if (ctx->ctx_handler == NO_THREAD)
		ctx->ctx_handler = pthread_self();

	if (err == ETIMEDOUT)
		return (1);

	return (0);
}
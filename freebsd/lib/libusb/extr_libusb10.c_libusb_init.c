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
struct libusb_context {int debug_fixed; int /*<<< orphan*/ * ctrl_pipe; int /*<<< orphan*/  ctx_poll; int /*<<< orphan*/  ctx_cond; int /*<<< orphan*/  hotplug_lock; int /*<<< orphan*/  ctx_lock; void* hotplug_handler; void* ctx_handler; int /*<<< orphan*/  hotplug_devs; int /*<<< orphan*/  hotplug_cbh; int /*<<< orphan*/  tr_done; int /*<<< orphan*/  pollfds; scalar_t__ debug; } ;
typedef  int /*<<< orphan*/  pthread_condattr_t ;
typedef  struct libusb_context libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DPRINTF (struct libusb_context*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NO_MEM ; 
 int LIBUSB_ERROR_OTHER ; 
 void* NO_THREAD ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_context_lock ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct libusb_context*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  libusb10_add_pollfd (struct libusb_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_set_nonblocking (int /*<<< orphan*/ ) ; 
 struct libusb_context* malloc (int) ; 
 int /*<<< orphan*/  memset (struct libusb_context*,int /*<<< orphan*/ ,int) ; 
 int pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_condattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_condattr_setclock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 struct libusb_context* usbi_default_context ; 

int
libusb_init(libusb_context **context)
{
	struct libusb_context *ctx;
	pthread_condattr_t attr;
	char *debug, *ep;
	int ret;

	ctx = malloc(sizeof(*ctx));
	if (!ctx)
		return (LIBUSB_ERROR_INVALID_PARAM);

	memset(ctx, 0, sizeof(*ctx));

	debug = getenv("LIBUSB_DEBUG");
	if (debug != NULL) {
		/*
		 * If LIBUSB_DEBUG is set, we'll honor that and use it to
		 * override libusb_set_debug calls.
		 */
		errno = 0;
		ctx->debug = strtol(debug, &ep, 10);
		if (errno == 0 && *ep == '\0') {
			ctx->debug_fixed = 1;
		} else {
			/*
			 * LIBUSB_DEBUG conversion failed for some reason, but
			 * we don't care about the specifics all that much.  We
			 * can't use it either way.  Force it to the default,
			 * 0, in case we had a partial number.
			 */
			ctx->debug = 0;
		}
	}
	TAILQ_INIT(&ctx->pollfds);
	TAILQ_INIT(&ctx->tr_done);
	TAILQ_INIT(&ctx->hotplug_cbh);
	TAILQ_INIT(&ctx->hotplug_devs);

	if (pthread_mutex_init(&ctx->ctx_lock, NULL) != 0) {
		free(ctx);
		return (LIBUSB_ERROR_NO_MEM);
	}
	if (pthread_mutex_init(&ctx->hotplug_lock, NULL) != 0) {
		pthread_mutex_destroy(&ctx->ctx_lock);
		free(ctx);
		return (LIBUSB_ERROR_NO_MEM);
	}
	if (pthread_condattr_init(&attr) != 0) {
		pthread_mutex_destroy(&ctx->ctx_lock);
		pthread_mutex_destroy(&ctx->hotplug_lock);
		free(ctx);
		return (LIBUSB_ERROR_NO_MEM);
	}
	if (pthread_condattr_setclock(&attr, CLOCK_MONOTONIC) != 0) {
		pthread_mutex_destroy(&ctx->ctx_lock);
		pthread_mutex_destroy(&ctx->hotplug_lock);
		pthread_condattr_destroy(&attr);
		free(ctx);
		return (LIBUSB_ERROR_OTHER);
	}
	if (pthread_cond_init(&ctx->ctx_cond, &attr) != 0) {
		pthread_mutex_destroy(&ctx->ctx_lock);
		pthread_mutex_destroy(&ctx->hotplug_lock);
		pthread_condattr_destroy(&attr);
		free(ctx);
		return (LIBUSB_ERROR_NO_MEM);
	}
	pthread_condattr_destroy(&attr);

	ctx->ctx_handler = NO_THREAD;
	ctx->hotplug_handler = NO_THREAD;

	ret = pipe(ctx->ctrl_pipe);
	if (ret < 0) {
		pthread_mutex_destroy(&ctx->ctx_lock);
		pthread_mutex_destroy(&ctx->hotplug_lock);
		pthread_cond_destroy(&ctx->ctx_cond);
		free(ctx);
		return (LIBUSB_ERROR_OTHER);
	}
	/* set non-blocking mode on the control pipe to avoid deadlock */
	libusb_set_nonblocking(ctx->ctrl_pipe[0]);
	libusb_set_nonblocking(ctx->ctrl_pipe[1]);

	libusb10_add_pollfd(ctx, &ctx->ctx_poll, NULL, ctx->ctrl_pipe[0], POLLIN);

	pthread_mutex_lock(&default_context_lock);
	if (usbi_default_context == NULL) {
		usbi_default_context = ctx;
	}
	pthread_mutex_unlock(&default_context_lock);

	if (context)
		*context = ctx;

	DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "libusb_init complete");

	return (0);
}
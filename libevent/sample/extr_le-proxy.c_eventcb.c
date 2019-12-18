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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 scalar_t__ ERR_func_error_string (unsigned long) ; 
 scalar_t__ ERR_lib_error_string (unsigned long) ; 
 scalar_t__ ERR_reason_error_string (unsigned long) ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 unsigned long bufferevent_get_openssl_error (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (struct bufferevent*,short,void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_on_finished_writecb ; 
 scalar_t__ errno ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  readcb (struct bufferevent*,void*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
eventcb(struct bufferevent *bev, short what, void *ctx)
{
	struct bufferevent *partner = ctx;

	if (what & (BEV_EVENT_EOF|BEV_EVENT_ERROR)) {
		if (what & BEV_EVENT_ERROR) {
			unsigned long err;
			while ((err = (bufferevent_get_openssl_error(bev)))) {
				const char *msg = (const char*)
				    ERR_reason_error_string(err);
				const char *lib = (const char*)
				    ERR_lib_error_string(err);
				const char *func = (const char*)
				    ERR_func_error_string(err);
				fprintf(stderr,
				    "%s in %s %s\n", msg, lib, func);
			}
			if (errno)
				perror("connection error");
		}

		if (partner) {
			/* Flush all pending data */
			readcb(bev, ctx);

			if (evbuffer_get_length(
				    bufferevent_get_output(partner))) {
				/* We still have to flush data from the other
				 * side, but when that's done, close the other
				 * side. */
				bufferevent_setcb(partner,
				    NULL, close_on_finished_writecb,
				    eventcb, NULL);
				bufferevent_disable(partner, EV_READ);
			} else {
				/* We have nothing left to say to the other
				 * side; close it. */
				bufferevent_free(partner);
			}
		}
		bufferevent_free(bev);
	}
}
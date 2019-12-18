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
struct event_config {int dummy; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int EV_CLOSED ; 
 int /*<<< orphan*/  EV_FEATURE_EARLY_CLOSE ; 
 int EV_TIMEOUT ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  closed_cb ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 int /*<<< orphan*/  event_config_require_features (struct event_config*,int /*<<< orphan*/ ) ; 
 struct event* event_new (struct event_base*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_self_cbarg () ; 
 int evutil_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  timeout ; 

int
main(int argc, char **argv)
{
	struct event_base *base;
	struct event_config *cfg;
	struct event *ev;
	const char *test = "test string";
	evutil_socket_t pair[2];

	/* Initialize the library and check if the backend
	   supports EV_FEATURE_EARLY_CLOSE
	*/
	cfg = event_config_new();
	event_config_require_features(cfg, EV_FEATURE_EARLY_CLOSE);
	base = event_base_new_with_config(cfg);
	event_config_free(cfg);
	if (!base) {
		/* Backend doesn't support EV_FEATURE_EARLY_CLOSE */
		return 0;
	}

	/* Create a pair of sockets */
	if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, pair) == -1)
		return (1);

	/* Send some data on socket 0 and immediately close it */
	if (send(pair[0], test, (int)strlen(test)+1, 0) < 0)
		return (1);
	shutdown(pair[0], SHUT_WR);

	/* Dispatch */
	ev = event_new(base, pair[1], EV_CLOSED | EV_TIMEOUT, closed_cb, event_self_cbarg());
	event_add(ev, &timeout);
	event_base_dispatch(base);

	/* Finalize library */
	event_base_free(base);
	return 0;
}
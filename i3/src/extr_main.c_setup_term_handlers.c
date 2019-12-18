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
struct ev_signal {int dummy; } ;
typedef  int /*<<< orphan*/  signal_watchers ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  ev_signal_init (struct ev_signal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_signal_start (int /*<<< orphan*/ ,struct ev_signal*) ; 
 int /*<<< orphan*/  ev_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_term_signal ; 
 int /*<<< orphan*/  main_loop ; 

__attribute__((used)) static void setup_term_handlers(void) {
    static struct ev_signal signal_watchers[6];
    size_t num_watchers = sizeof(signal_watchers) / sizeof(signal_watchers[0]);

    /* We have to rely on libev functionality here and should not use
     * sigaction handlers because we need to invoke the exit handlers
     * and cannot do so from an asynchronous signal handling context as
     * not all code triggered during exit is signal safe (and exiting
     * the main loop from said handler is not easily possible). libev's
     * signal handlers does not impose such a constraint on us. */
    ev_signal_init(&signal_watchers[0], handle_term_signal, SIGHUP);
    ev_signal_init(&signal_watchers[1], handle_term_signal, SIGINT);
    ev_signal_init(&signal_watchers[2], handle_term_signal, SIGALRM);
    ev_signal_init(&signal_watchers[3], handle_term_signal, SIGTERM);
    ev_signal_init(&signal_watchers[4], handle_term_signal, SIGUSR1);
    ev_signal_init(&signal_watchers[5], handle_term_signal, SIGUSR1);
    for (size_t i = 0; i < num_watchers; i++) {
        ev_signal_start(main_loop, &signal_watchers[i]);
        /* The signal handlers should not block ev_run from returning
         * and so none of the signal handlers should hold a reference to
         * the main loop. */
        ev_unref(main_loop);
    }
}
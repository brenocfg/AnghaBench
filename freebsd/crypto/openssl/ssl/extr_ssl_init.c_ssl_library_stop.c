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

/* Variables and functions */
 int /*<<< orphan*/  err_free_strings_int () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ssl_base_inited ; 
 int /*<<< orphan*/  ssl_comp_free_compression_methods_int () ; 
 scalar_t__ ssl_strings_inited ; 
 int /*<<< orphan*/  stderr ; 
 int stopped ; 

__attribute__((used)) static void ssl_library_stop(void)
{
    /* Might be explicitly called and also by atexit */
    if (stopped)
        return;
    stopped = 1;

    if (ssl_base_inited) {
#ifndef OPENSSL_NO_COMP
# ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: ssl_library_stop: "
                "ssl_comp_free_compression_methods_int()\n");
# endif
        ssl_comp_free_compression_methods_int();
#endif
    }

    if (ssl_strings_inited) {
#ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: ssl_library_stop: "
                "err_free_strings_int()\n");
#endif
        /*
         * If both crypto and ssl error strings are inited we will end up
         * calling err_free_strings_int() twice - but that's ok. The second
         * time will be a no-op. It's easier to do that than to try and track
         * between the two libraries whether they have both been inited.
         */
        err_free_strings_int();
    }
}
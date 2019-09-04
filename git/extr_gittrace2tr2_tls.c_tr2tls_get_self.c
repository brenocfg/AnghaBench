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
struct tr2tls_thread_ctx {int dummy; } ;

/* Variables and functions */
 struct tr2tls_thread_ctx* pthread_getspecific (int /*<<< orphan*/ ) ; 
 struct tr2tls_thread_ctx* tr2tls_create_self (char*) ; 
 int /*<<< orphan*/  tr2tls_key ; 

struct tr2tls_thread_ctx *tr2tls_get_self(void)
{
	struct tr2tls_thread_ctx *ctx = pthread_getspecific(tr2tls_key);

	/*
	 * If the thread-proc did not call trace2_thread_start(), we won't
	 * have any TLS data associated with the current thread.  Fix it
	 * here and silently continue.
	 */
	if (!ctx)
		ctx = tr2tls_create_self("unknown");

	return ctx;
}
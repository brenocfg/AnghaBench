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
struct tr2tls_thread_ctx {struct tr2tls_thread_ctx* array_us_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tr2tls_thread_ctx*) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 
 int /*<<< orphan*/  tr2tls_key ; 

void tr2tls_unset_self(void)
{
	struct tr2tls_thread_ctx *ctx;

	ctx = tr2tls_get_self();

	pthread_setspecific(tr2tls_key, NULL);

	free(ctx->array_us_start);
	free(ctx);
}
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
typedef  int /*<<< orphan*/  h2o_memcached_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  reader_main (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *thread_main(void *_ctx)
{
    h2o_memcached_context_t *ctx = _ctx;

    while (1)
        reader_main(ctx);
    return NULL;
}
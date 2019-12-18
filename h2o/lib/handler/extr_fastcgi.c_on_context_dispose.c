#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_4__ {int /*<<< orphan*/  sockpool; } ;
typedef  TYPE_1__ h2o_fastcgi_handler_t ;
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_2__ h2o_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_socketpool_unregister_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_context_dispose(h2o_handler_t *_handler, h2o_context_t *ctx)
{
    h2o_fastcgi_handler_t *handler = (void *)_handler;
    h2o_socketpool_unregister_loop(&handler->sockpool, ctx->loop);
}
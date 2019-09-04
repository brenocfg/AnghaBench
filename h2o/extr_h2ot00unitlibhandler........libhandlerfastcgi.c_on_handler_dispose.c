#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* dispose ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__ document_root; TYPE_1__ callbacks; } ;
struct TYPE_9__ {TYPE_3__ config; int /*<<< orphan*/  sockpool; } ;
typedef  TYPE_4__ h2o_fastcgi_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socketpool_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_handler_dispose(h2o_handler_t *_handler)
{
    h2o_fastcgi_handler_t *handler = (void *)_handler;

    if (handler->config.callbacks.dispose != NULL)
        handler->config.callbacks.dispose(handler, handler->config.callbacks.data);

    h2o_socketpool_dispose(&handler->sockpool);
    free(handler->config.document_root.base);
}
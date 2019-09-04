#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* base; } ;
struct TYPE_6__ {TYPE_3__* path; TYPE_1__ source; } ;
struct TYPE_7__ {TYPE_2__ config; } ;
typedef  TYPE_3__ h2o_mruby_handler_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void on_handler_dispose(h2o_handler_t *_handler)
{
    h2o_mruby_handler_t *handler = (void *)_handler;

    free(handler->config.source.base);
    free(handler->config.path);
    free(handler);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_6__ {int /*<<< orphan*/ * base; } ;
struct TYPE_5__ {int /*<<< orphan*/ * base; } ;
struct TYPE_8__ {TYPE_3__* index_files; int /*<<< orphan*/  mimemap; TYPE_2__ real_path; TYPE_1__ conf_path; } ;
typedef  TYPE_4__ h2o_file_handler_t ;
struct TYPE_7__ {int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_handler_dispose(h2o_handler_t *_self)
{
    h2o_file_handler_t *self = (void *)_self;
    size_t i;

    free(self->conf_path.base);
    free(self->real_path.base);
    h2o_mem_release_shared(self->mimemap);
    for (i = 0; self->index_files[i].base != NULL; ++i)
        free(self->index_files[i].base);
}
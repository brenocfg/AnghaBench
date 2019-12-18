#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct st_h2o_specific_file_handler_t {int /*<<< orphan*/  mime_type; TYPE_1__ real_path; } ;
typedef  int /*<<< orphan*/  h2o_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void specific_handler_on_dispose(h2o_handler_t *_self)
{
    struct st_h2o_specific_file_handler_t *self = (void *)_self;

    free(self->real_path.base);
    h2o_mem_release_shared(self->mime_type);
}
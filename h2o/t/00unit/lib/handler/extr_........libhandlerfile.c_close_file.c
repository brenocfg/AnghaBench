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
struct TYPE_2__ {int /*<<< orphan*/ * ref; } ;
struct st_h2o_sendfile_generator_t {TYPE_1__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_filecache_close_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_file(struct st_h2o_sendfile_generator_t *self)
{
    if (self->file.ref != NULL) {
        h2o_filecache_close_file(self->file.ref);
        self->file.ref = NULL;
    }
}
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
struct st_h2o_access_logger_t {int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  h2o_logger_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispose(h2o_logger_t *_self)
{
    struct st_h2o_access_logger_t *self = (void *)_self;

    h2o_mem_release_shared(self->fh);
}
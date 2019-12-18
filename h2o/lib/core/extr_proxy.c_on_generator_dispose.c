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
struct rp_generator_t {int /*<<< orphan*/  sending; int /*<<< orphan*/ * last_content_before_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_close (struct rp_generator_t*) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_doublebuffer_dispose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_generator_dispose(void *_self)
{
    struct rp_generator_t *self = _self;
    do_close(self);

    if (self->last_content_before_send != NULL) {
        h2o_buffer_dispose(&self->last_content_before_send);
    }
    h2o_doublebuffer_dispose(&self->sending);
}
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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {TYPE_2__* generator; } ;
typedef  TYPE_3__ h2o_mruby_error_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  error_stream; } ;
struct TYPE_6__ {TYPE_1__ refs; int /*<<< orphan*/ * error_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static void on_gc_dispose_error_stream(mrb_state *mrb, void *_error_stream)
{
    h2o_mruby_error_stream_t *error_stream = _error_stream;
    if (error_stream == NULL)
        return;
    if (error_stream->generator != NULL) {
        error_stream->generator->error_stream = NULL;
        error_stream->generator->refs.error_stream = mrb_nil_value();
    }
    free(error_stream);
}
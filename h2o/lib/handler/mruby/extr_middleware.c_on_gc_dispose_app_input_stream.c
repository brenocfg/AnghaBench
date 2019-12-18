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
struct TYPE_2__ {int /*<<< orphan*/  request; int /*<<< orphan*/  input_stream; } ;
struct st_mruby_subreq_t {TYPE_1__ refs; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  dispose_subreq (struct st_mruby_subreq_t*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static void on_gc_dispose_app_input_stream(mrb_state *mrb, void *_subreq)
{
    struct st_mruby_subreq_t *subreq = _subreq;
    if (subreq == NULL)
        return;
    subreq->refs.input_stream = mrb_nil_value();
    if (mrb_nil_p(subreq->refs.request))
        dispose_subreq(subreq);
}
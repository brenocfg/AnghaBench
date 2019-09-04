#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int /*<<< orphan*/  generator; } ;
struct TYPE_4__ {TYPE_1__ refs; } ;
typedef  TYPE_2__ h2o_mruby_generator_t ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static void on_gc_dispose_generator(mrb_state *mrb, void *_generator)
{
    h2o_mruby_generator_t *generator = _generator;
    if (generator == NULL)
        return;
    generator->refs.generator = mrb_nil_value();
}
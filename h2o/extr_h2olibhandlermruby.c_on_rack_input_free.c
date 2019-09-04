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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static void on_rack_input_free(mrb_state *mrb, const char *base, mrb_int len, void *_input_stream)
{
    /* reset ref to input_stream */
    mrb_value *input_stream = _input_stream;
    *input_stream = mrb_nil_value();
}
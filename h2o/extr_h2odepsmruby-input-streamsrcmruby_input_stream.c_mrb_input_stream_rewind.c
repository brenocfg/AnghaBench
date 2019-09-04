#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {scalar_t__ pos; } ;
typedef  TYPE_1__ mrb_input_stream_t ;

/* Variables and functions */
 TYPE_1__* DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_is_open (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static mrb_value
mrb_input_stream_rewind(mrb_state *mrb, mrb_value self)
{
  mrb_input_stream_t *stream = DATA_PTR(self);
  assert_is_open(mrb, stream);
  stream->pos = 0;
  return self;
}
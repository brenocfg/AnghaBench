#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_BLOCK () ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_input_stream_byteindex ; 
 int /*<<< orphan*/  mrb_input_stream_gets ; 
 int /*<<< orphan*/  mrb_input_stream_init ; 
 int /*<<< orphan*/  mrb_input_stream_read ; 
 int /*<<< orphan*/  mrb_input_stream_rewind ; 

void
mrb_mruby_input_stream_gem_init(mrb_state* mrb)
{
  struct RClass * c = mrb_define_class(mrb, "InputStream", mrb->object_class);

  mrb_define_method(mrb, c, "gets",  mrb_input_stream_gets,  MRB_ARGS_NONE());
  mrb_define_method(mrb, c, "read",  mrb_input_stream_read,  MRB_ARGS_ANY());
  mrb_define_method(mrb, c, "initialize",  mrb_input_stream_init,  MRB_ARGS_BLOCK());
  mrb_define_method(mrb, c, "rewind",  mrb_input_stream_rewind,  MRB_ARGS_NONE());
  mrb_define_method(mrb, c, "byteindex",  mrb_input_stream_byteindex,  MRB_ARGS_ANY());
}
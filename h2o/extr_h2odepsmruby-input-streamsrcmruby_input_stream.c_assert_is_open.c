#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {scalar_t__ len; } ;
typedef  TYPE_1__ mrb_input_stream_t ;

/* Variables and functions */
 struct RClass* E_RUNTIME_ERROR ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,struct RClass*,char*) ; 

__attribute__((used)) static void
assert_is_open(mrb_state *mrb, mrb_input_stream_t *stream)
{
  if (stream->len < 0) {
    struct RClass *klass = mrb_class_get(mrb, "IOError");
    if (klass == NULL)
      klass = E_RUNTIME_ERROR;
    mrb_raise(mrb, klass, "stream closed");
  }
}
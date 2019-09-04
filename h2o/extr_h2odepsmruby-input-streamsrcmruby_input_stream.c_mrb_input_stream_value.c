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
struct RData {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;
typedef  int /*<<< orphan*/  mrb_input_stream_t ;

/* Variables and functions */
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 struct RData* mrb_data_object_alloc (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mrb_input_stream_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_input_stream_type ; 
 int /*<<< orphan*/  mrb_obj_value (struct RData*) ; 

mrb_value
mrb_input_stream_value(mrb_state *mrb, const char *base, mrb_int len)
{
  mrb_input_stream_t *stream = mrb_input_stream_create(mrb, base, len, NULL, NULL);
  struct RClass *c = mrb_class_get(mrb, "InputStream");
  struct RData *d = mrb_data_object_alloc(mrb, c, stream, &mrb_input_stream_type);

  return mrb_obj_value(d);
}
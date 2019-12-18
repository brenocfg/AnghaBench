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
typedef  void* mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  double mrb_int ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Object ;
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
#define  JSONArray 135 
#define  JSONBoolean 134 
#define  JSONError 133 
#define  JSONFixed 132 
#define  JSONNull 131 
#define  JSONNumber 130 
#define  JSONObject 129 
#define  JSONString 128 
 double floor (double) ; 
 size_t json_array_get_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_array_get_value (int /*<<< orphan*/ *,size_t) ; 
 size_t json_object_get_count (int /*<<< orphan*/ *) ; 
 char* json_object_get_name (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * json_object_get_value (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * json_value_get_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_value_get_boolean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_value_get_fixed (int /*<<< orphan*/ *) ; 
 double json_value_get_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_get_object (int /*<<< orphan*/ *) ; 
 char const* json_value_get_string (int /*<<< orphan*/ *) ; 
 int json_value_get_type (int /*<<< orphan*/ *) ; 
 void* mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,void*,void*) ; 
 void* mrb_false_value () ; 
 void* mrb_fixnum_value (double) ; 
 void* mrb_float_value (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 void* mrb_hash_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_hash_set (int /*<<< orphan*/ *,void*,void*,void*) ; 
 void* mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 void* mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 
 void* mrb_true_value () ; 

__attribute__((used)) static mrb_value
json_value_to_mrb_value(mrb_state* mrb, JSON_Value* value) {
  mrb_value ret;
  switch (json_value_get_type(value)) {
  case JSONError:
  case JSONNull:
    ret = mrb_nil_value();
    break;
  case JSONString:
    ret = mrb_str_new_cstr(mrb, json_value_get_string(value));
    break;
#ifdef JSON_FIXED_NUMBER
  case JSONFixed:
    ret = mrb_fixnum_value((mrb_int)json_value_get_fixed(value));
    break;
  case JSONNumber:
    ret = mrb_float_value(mrb, json_value_get_number(value));
    break;
#else
  case JSONNumber:
    {
      double d = json_value_get_number(value);
      if (floor(d) == d) {
        ret = mrb_fixnum_value(d);
      }
      else {
        ret = mrb_float_value(mrb, d);
      }
    }
    break;
#endif
  case JSONObject:
    {
      mrb_value hash = mrb_hash_new(mrb);
      JSON_Object* object = json_value_get_object(value);
      size_t count = json_object_get_count(object);
      size_t n;
      for (n = 0; n < count; n++) {
        int ai = mrb_gc_arena_save(mrb);
        const char* name = json_object_get_name(object, n);
        mrb_hash_set(mrb, hash, mrb_str_new_cstr(mrb, name),
          json_value_to_mrb_value(mrb, json_object_get_value(object, name)));
        mrb_gc_arena_restore(mrb, ai);
      }
      ret = hash;
    }
    break;
  case JSONArray:
    {
      mrb_value ary;
      JSON_Array* array;
      size_t n, count;
      ary = mrb_ary_new(mrb);
      array = json_value_get_array(value);
      count = json_array_get_count(array);
      for (n = 0; n < count; n++) {
        int ai = mrb_gc_arena_save(mrb);
        JSON_Value* elem = json_array_get_value(array, n);
        mrb_ary_push(mrb, ary, json_value_to_mrb_value(mrb, elem));
        mrb_gc_arena_restore(mrb, ai);
      }
      ret = ary;
    }
    break;
  case JSONBoolean:
    if (json_value_get_boolean(value))
      ret = mrb_true_value();
    else
      ret = mrb_false_value();
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid argument");
  }
  return ret;
}
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

/* Variables and functions */
#define  MRB_TT_ARRAY 136 
#define  MRB_TT_FALSE 135 
#define  MRB_TT_FIXNUM 134 
#define  MRB_TT_FLOAT 133 
#define  MRB_TT_HASH 132 
#define  MRB_TT_STRING 131 
#define  MRB_TT_SYMBOL 130 
#define  MRB_TT_TRUE 129 
#define  MRB_TT_UNDEF 128 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_END (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_hash_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_method_defined (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pretty_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static mrb_value
mrb_value_to_string(mrb_state* mrb, mrb_value value, int pretty) {
  mrb_value str;

  if (mrb_nil_p(value)) {
    return mrb_str_new_cstr(mrb, "null");
  }

  switch (mrb_type(value)) {
  case MRB_TT_FIXNUM:
  case MRB_TT_FLOAT:
  case MRB_TT_TRUE:
  case MRB_TT_FALSE:
  case MRB_TT_UNDEF:
    str = mrb_funcall(mrb, value, "to_s", 0, NULL);
    break;
  case MRB_TT_SYMBOL:
    value = mrb_funcall(mrb, value, "to_s", 0, NULL);
    /* FALLTHROUGH */
  case MRB_TT_STRING:
    {
      int ai = mrb_gc_arena_save(mrb);
      char* ptr = RSTRING_PTR(value);
      char* end = RSTRING_END(value);
      str = mrb_str_new_cstr(mrb, "\""); 
      while (ptr < end && *ptr) {
        switch (*ptr) {
        case '\\':
          str = mrb_str_cat_cstr(mrb, str, "\\\\");
          break;
        case '"':
          str = mrb_str_cat_cstr(mrb, str, "\\\"");
          break;
        case '\b':
          str = mrb_str_cat_cstr(mrb, str, "\\b");
          break;
        case '\f':
          str = mrb_str_cat_cstr(mrb, str, "\\f");
          break;
        case '\n':
          str = mrb_str_cat_cstr(mrb, str, "\\n");
          break;
        case '\r':
          str = mrb_str_cat_cstr(mrb, str, "\\r");
          break;
        case '\t':
          str = mrb_str_cat_cstr(mrb, str, "\\t");
          break;
        default:
          // TODO: handle unicode
          str = mrb_str_cat(mrb, str, ptr, 1);
        }
        ptr++;
      }
      mrb_str_cat_cstr(mrb, str, "\""); 
      mrb_gc_arena_restore(mrb, ai);
    }
    break;
  case MRB_TT_HASH:
    {
      mrb_value keys;
      int n, l;

      str = mrb_str_new_cstr(mrb, "{");
      keys = mrb_hash_keys(mrb, value);
      l = RARRAY_LEN(keys);
      if (l == 0) {
        if (pretty >= 0) return mrb_str_cat_cstr(mrb, str, "\n}");
        return mrb_str_cat_cstr(mrb, str, "}");
      }
      if (pretty >= 0) str = pretty_cat(mrb, str, ++pretty);
      for (n = 0; n < l; n++) {
        mrb_value obj;
        int ai = mrb_gc_arena_save(mrb);
        mrb_value key = mrb_ary_entry(keys, n);
        mrb_value enckey = mrb_funcall(mrb, key, "to_s", 0, NULL);
        enckey = mrb_funcall(mrb, enckey, "inspect", 0, NULL);
        mrb_str_concat(mrb, str, enckey);
        mrb_str_cat_cstr(mrb, str, ":");
        obj = mrb_hash_get(mrb, value, key);
        mrb_str_concat(mrb, str, mrb_value_to_string(mrb, obj, pretty));
        if (n != l - 1) {
          mrb_str_cat_cstr(mrb, str, ",");
          if (pretty >= 0) str = pretty_cat(mrb, str, pretty);
        }
        mrb_gc_arena_restore(mrb, ai);
      }
      if (pretty >= 0) str = pretty_cat(mrb, str, --pretty);
      mrb_str_cat_cstr(mrb, str, "}");
      break;
    }
  case MRB_TT_ARRAY:
    {
      int n, l;

      str = mrb_str_new_cstr(mrb, "[");
      l = RARRAY_LEN(value);
      if (l == 0) {
        if (pretty >= 0) return mrb_str_cat_cstr(mrb, str, "\n]");
        return mrb_str_cat_cstr(mrb, str, "]");
      }
      if (pretty >= 0) str = pretty_cat(mrb, str, ++pretty);
      for (n = 0; n < l; n++) {
        int ai = mrb_gc_arena_save(mrb);
        mrb_value obj = mrb_ary_entry(value, n);
        mrb_str_concat(mrb, str, mrb_value_to_string(mrb, obj, pretty));
        if (n != l - 1) {
          mrb_str_cat_cstr(mrb, str, ",");
          if (pretty >= 0) str = pretty_cat(mrb, str, pretty);
        }
        mrb_gc_arena_restore(mrb, ai);
      }
      if (pretty >= 0) str = pretty_cat(mrb, str, --pretty);
      mrb_str_cat_cstr(mrb, str, "]");
      break;
    }
  default:
    {
      if (mrb_method_defined(mrb, value, "to_json"))
        str = mrb_funcall(mrb, value, "to_json", 0, NULL);
      else
        str = mrb_value_to_string(mrb, mrb_funcall(mrb, value, "to_s", 0, NULL), pretty);
    }
  } 
  return str;
}
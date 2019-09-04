#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* capa; } ;
struct TYPE_5__ {char* ptr; TYPE_1__ aux; void* len; } ;
struct TYPE_6__ {char* ary; TYPE_2__ heap; } ;
struct RString {TYPE_3__ as; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  void* mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 size_t MRB_INT_MAX ; 
 size_t RSTRING_EMBED_LEN_MAX ; 
 char* RSTR_PTR (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_EMBED_FLAG (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_EMBED_LEN (struct RString*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 struct RString* mrb_obj_alloc_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_ro_data_p (char const*) ; 
 struct RString* str_new_static (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static struct RString*
str_new(mrb_state *mrb, const char *p, size_t len)
{
  struct RString *s;

  if (p && mrb_ro_data_p(p)) {
    return str_new_static(mrb, p, len);
  }
  s = mrb_obj_alloc_string(mrb);
  if (len <= RSTRING_EMBED_LEN_MAX) {
    RSTR_SET_EMBED_FLAG(s);
    RSTR_SET_EMBED_LEN(s, len);
    if (p) {
      memcpy(s->as.ary, p, len);
    }
  }
  else {
    if (len >= MRB_INT_MAX) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "string size too big");
    }
    s->as.heap.ptr = (char *)mrb_malloc(mrb, len+1);
    s->as.heap.len = (mrb_int)len;
    s->as.heap.aux.capa = (mrb_int)len;
    if (p) {
      memcpy(s->as.heap.ptr, p, len);
    }
  }
  RSTR_PTR(s)[len] = '\0';
  return s;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t capa; } ;
struct TYPE_8__ {char* ptr; size_t len; TYPE_1__ aux; } ;
struct TYPE_9__ {char* ary; TYPE_2__ heap; } ;
struct RString {TYPE_3__ as; scalar_t__ flags; int /*<<< orphan*/  c; int /*<<< orphan*/  tt; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_10__ {int /*<<< orphan*/  string_class; } ;
typedef  TYPE_4__ mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_SET_FROZEN_FLAG (struct RString*) ; 
 scalar_t__ MRB_STR_NOFREE ; 
 int /*<<< orphan*/  MRB_TT_STRING ; 
 size_t RSTRING_EMBED_LEN_MAX ; 
 size_t RSTR_EMBED_LEN (struct RString*) ; 
 scalar_t__ RSTR_EMBED_P (struct RString*) ; 
 scalar_t__ RSTR_NOFREE_P (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_EMBED_FLAG (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_EMBED_LEN (struct RString*,size_t) ; 
 int /*<<< orphan*/  RSTR_SET_POOL_FLAG (struct RString*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ mrb_malloc (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RString*) ; 
 struct RString* mrb_str_ptr (int /*<<< orphan*/ ) ; 

mrb_value
mrb_str_pool(mrb_state *mrb, mrb_value str)
{
  struct RString *s = mrb_str_ptr(str);
  struct RString *ns;
  char *ptr;
  mrb_int len;

  ns = (struct RString *)mrb_malloc(mrb, sizeof(struct RString));
  ns->tt = MRB_TT_STRING;
  ns->c = mrb->string_class;

  if (RSTR_NOFREE_P(s)) {
    ns->flags = MRB_STR_NOFREE;
    ns->as.heap.ptr = s->as.heap.ptr;
    ns->as.heap.len = s->as.heap.len;
    ns->as.heap.aux.capa = 0;
  }
  else {
    ns->flags = 0;
    if (RSTR_EMBED_P(s)) {
      ptr = s->as.ary;
      len = RSTR_EMBED_LEN(s);
    }
    else {
      ptr = s->as.heap.ptr;
      len = s->as.heap.len;
    }

    if (len < RSTRING_EMBED_LEN_MAX) {
      RSTR_SET_EMBED_FLAG(ns);
      RSTR_SET_EMBED_LEN(ns, len);
      if (ptr) {
        memcpy(ns->as.ary, ptr, len);
      }
      ns->as.ary[len] = '\0';
    }
    else {
      ns->as.heap.ptr = (char *)mrb_malloc(mrb, (size_t)len+1);
      ns->as.heap.len = len;
      ns->as.heap.aux.capa = len;
      if (ptr) {
        memcpy(ns->as.heap.ptr, ptr, len);
      }
      ns->as.heap.ptr[len] = '\0';
    }
  }
  RSTR_SET_POOL_FLAG(ns);
  MRB_SET_FROZEN_FLAG(ns);
  return mrb_obj_value(ns);
}
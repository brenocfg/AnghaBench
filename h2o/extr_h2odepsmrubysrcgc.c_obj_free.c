#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {TYPE_7__* cibase; TYPE_7__* ci; int /*<<< orphan*/  status; } ;
struct RString {int dummy; } ;
struct RRange {int dummy; } ;
struct TYPE_25__ {int /*<<< orphan*/ * irep; } ;
struct RProc {TYPE_4__ body; } ;
struct RObject {int dummy; } ;
struct RHash {int dummy; } ;
struct RFiber {struct mrb_context* cxt; } ;
struct REnv {int const tt; int /*<<< orphan*/ * stack; } ;
struct RData {int /*<<< orphan*/  data; TYPE_5__* type; } ;
struct RClass {int dummy; } ;
struct RBasic {int tt; } ;
struct TYPE_22__ {int /*<<< orphan*/  shared; } ;
struct TYPE_23__ {int /*<<< orphan*/ * ptr; TYPE_1__ aux; } ;
struct TYPE_24__ {TYPE_2__ heap; } ;
struct RArray {TYPE_3__ as; } ;
struct TYPE_27__ {struct mrb_context* root_c; } ;
typedef  TYPE_6__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
struct TYPE_28__ {struct REnv* env; } ;
typedef  TYPE_7__ mrb_callinfo ;
struct TYPE_26__ {int /*<<< orphan*/  (* dfree ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARY_EMBED_P (struct RBasic*) ; 
 int /*<<< orphan*/  ARY_SHARED_P (struct RBasic*) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_ENV_STACK_SHARED_P (struct REnv*) ; 
 int /*<<< orphan*/  MRB_FIBER_TERMINATED ; 
 int /*<<< orphan*/  MRB_FLAG_TEST (struct RBasic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_FL_CLASS_IS_ORIGIN ; 
 int /*<<< orphan*/  MRB_PROC_CFUNC_P (struct RProc*) ; 
#define  MRB_TT_ARRAY 145 
#define  MRB_TT_CLASS 144 
#define  MRB_TT_DATA 143 
#define  MRB_TT_ENV 142 
#define  MRB_TT_EXCEPTION 141 
#define  MRB_TT_FIBER 140 
#define  MRB_TT_FIXNUM 139 
#define  MRB_TT_FLOAT 138 
 int MRB_TT_FREE ; 
#define  MRB_TT_HASH 137 
#define  MRB_TT_ICLASS 136 
#define  MRB_TT_MODULE 135 
#define  MRB_TT_OBJECT 134 
#define  MRB_TT_PROC 133 
#define  MRB_TT_RANGE 132 
#define  MRB_TT_SCLASS 131 
#define  MRB_TT_STRING 130 
#define  MRB_TT_SYMBOL 129 
#define  MRB_TT_TRUE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct RBasic*,int) ; 
 int /*<<< orphan*/  mrb_ary_decref (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_env_unshare (TYPE_6__*,struct REnv*) ; 
 int /*<<< orphan*/  mrb_free (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free_context (TYPE_6__*,struct mrb_context*) ; 
 int /*<<< orphan*/  mrb_gc_free_hash (TYPE_6__*,struct RHash*) ; 
 int /*<<< orphan*/  mrb_gc_free_iv (TYPE_6__*,struct RObject*) ; 
 int /*<<< orphan*/  mrb_gc_free_mt (TYPE_6__*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_gc_free_range (TYPE_6__*,struct RRange*) ; 
 int /*<<< orphan*/  mrb_gc_free_str (TYPE_6__*,struct RString*) ; 
 int /*<<< orphan*/  mrb_irep_cutref (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_irep_decref (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_object_dead_p (TYPE_6__*,struct RBasic*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
obj_free(mrb_state *mrb, struct RBasic *obj, int end)
{
  DEBUG(fprintf(stderr, "obj_free(%p,tt=%d)\n",obj,obj->tt));
  switch (obj->tt) {
    /* immediate - no mark */
  case MRB_TT_TRUE:
  case MRB_TT_FIXNUM:
  case MRB_TT_SYMBOL:
    /* cannot happen */
    return;

#ifndef MRB_WITHOUT_FLOAT
  case MRB_TT_FLOAT:
#ifdef MRB_WORD_BOXING
    break;
#else
    return;
#endif
#endif

  case MRB_TT_OBJECT:
    mrb_gc_free_iv(mrb, (struct RObject*)obj);
    break;

  case MRB_TT_EXCEPTION:
    mrb_gc_free_iv(mrb, (struct RObject*)obj);
    break;

  case MRB_TT_CLASS:
  case MRB_TT_MODULE:
  case MRB_TT_SCLASS:
    mrb_gc_free_mt(mrb, (struct RClass*)obj);
    mrb_gc_free_iv(mrb, (struct RObject*)obj);
    break;
  case MRB_TT_ICLASS:
    if (MRB_FLAG_TEST(obj, MRB_FL_CLASS_IS_ORIGIN))
      mrb_gc_free_mt(mrb, (struct RClass*)obj);
    break;
  case MRB_TT_ENV:
    {
      struct REnv *e = (struct REnv*)obj;

      if (MRB_ENV_STACK_SHARED_P(e)) {
        /* cannot be freed */
        e->stack = NULL;
        break;
      }
      mrb_free(mrb, e->stack);
      e->stack = NULL;
    }
    break;

  case MRB_TT_FIBER:
    {
      struct mrb_context *c = ((struct RFiber*)obj)->cxt;

      if (c && c != mrb->root_c) {
        if (!end && c->status != MRB_FIBER_TERMINATED) {
          mrb_callinfo *ci = c->ci;
          mrb_callinfo *ce = c->cibase;

          while (ce <= ci) {
            struct REnv *e = ci->env;
            if (e && !mrb_object_dead_p(mrb, (struct RBasic*)e) &&
                e->tt == MRB_TT_ENV && MRB_ENV_STACK_SHARED_P(e)) {
              mrb_env_unshare(mrb, e);
            }
            ci--;
          }
        }
        mrb_free_context(mrb, c);
      }
    }
    break;

  case MRB_TT_ARRAY:
    if (ARY_SHARED_P(obj))
      mrb_ary_decref(mrb, ((struct RArray*)obj)->as.heap.aux.shared);
    else if (!ARY_EMBED_P(obj))
      mrb_free(mrb, ((struct RArray*)obj)->as.heap.ptr);
    break;

  case MRB_TT_HASH:
    mrb_gc_free_iv(mrb, (struct RObject*)obj);
    mrb_gc_free_hash(mrb, (struct RHash*)obj);
    break;

  case MRB_TT_STRING:
    mrb_gc_free_str(mrb, (struct RString*)obj);
    break;

  case MRB_TT_PROC:
    {
      struct RProc *p = (struct RProc*)obj;

      if (!MRB_PROC_CFUNC_P(p) && p->body.irep) {
        mrb_irep *irep = p->body.irep;
        if (end) {
          mrb_irep_cutref(mrb, irep);
        }
        mrb_irep_decref(mrb, irep);
      }
    }
    break;

  case MRB_TT_RANGE:
    mrb_gc_free_range(mrb, ((struct RRange*)obj));
    break;

  case MRB_TT_DATA:
    {
      struct RData *d = (struct RData*)obj;
      if (d->type && d->type->dfree) {
        d->type->dfree(mrb, d->data);
      }
      mrb_gc_free_iv(mrb, (struct RObject*)obj);
    }
    break;

  default:
    break;
  }
  obj->tt = MRB_TT_FREE;
}
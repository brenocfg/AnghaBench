#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct backtrace_location {int dummy; } ;
struct RData {unsigned int flags; } ;
typedef  TYPE_2__* ptrdiff_t ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_11__ {TYPE_1__* c; } ;
typedef  TYPE_3__ mrb_state ;
struct TYPE_10__ {int /*<<< orphan*/  pc; } ;
struct TYPE_9__ {int cibase; TYPE_2__* ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_type ; 
 int /*<<< orphan*/  count_backtrace_i ; 
 int /*<<< orphan*/  each_backtrace (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct RData* mrb_data_object_alloc (TYPE_3__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 void* mrb_malloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RData*) ; 
 int /*<<< orphan*/  pack_backtrace_i ; 

__attribute__((used)) static mrb_value
packed_backtrace(mrb_state *mrb)
{
  struct RData *backtrace;
  ptrdiff_t ciidx = mrb->c->ci - mrb->c->cibase;
  int len = 0;
  int size;
  void *ptr;

  each_backtrace(mrb, ciidx, mrb->c->ci->pc, count_backtrace_i, &len);
  size = len * sizeof(struct backtrace_location);
  ptr = mrb_malloc(mrb, size);
  if (ptr) memset(ptr, 0, size);
  backtrace = mrb_data_object_alloc(mrb, NULL, ptr, &bt_type);
  backtrace->flags = (unsigned int)len;
  each_backtrace(mrb, ciidx, mrb->c->ci->pc, pack_backtrace_i, &ptr);
  return mrb_obj_value(backtrace);
}
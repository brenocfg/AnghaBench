#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ segment ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ last_len; TYPE_1__* rootseg; } ;
typedef  TYPE_2__ iv_tbl ;

/* Variables and functions */
 scalar_t__ MRB_IV_SEGMENT_SIZE ; 

__attribute__((used)) static size_t
iv_size(mrb_state *mrb, iv_tbl *t)
{
  segment *seg;
  size_t size = 0;

  if (t == NULL) return 0;
  if (t->size > 0) return t->size;
  seg = t->rootseg;
  while (seg) {
    if (seg->next == NULL) {
      size += t->last_len;
      return size;
    }
    seg = seg->next;
    size += MRB_IV_SEGMENT_SIZE;
  }
  /* empty iv_tbl */
  return 0;
}
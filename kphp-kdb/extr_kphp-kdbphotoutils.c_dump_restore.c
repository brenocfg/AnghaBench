#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vptr ;
struct TYPE_2__ {int /*<<< orphan*/  val; struct TYPE_2__* next; } ;
typedef  TYPE_1__ restore_list ;

/* Variables and functions */
 int /*<<< orphan*/  CONV_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _restore_info ; 
 scalar_t__ _restore_info_maxn ; 
 scalar_t__ _restore_info_n ; 
 int /*<<< orphan*/  assert (int) ; 

void dump_restore (int *i, vptr *_v) {
  restore_list *v = *(restore_list **)_v;

  assert (_restore_info_n < _restore_info_maxn);
  _restore_info[_restore_info_n++] = CONV_ID (v->val);

  restore_list *end = v;
  while (v->next != end) {
    v = v->next;

    assert (_restore_info_n < _restore_info_maxn);
    _restore_info[_restore_info_n++] = v->val;
  }
}
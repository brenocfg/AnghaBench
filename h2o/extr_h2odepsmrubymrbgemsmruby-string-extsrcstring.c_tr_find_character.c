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
struct TYPE_2__ {int start_pos; int* ch; } ;
struct tr_pattern {scalar_t__ flag_reverse; scalar_t__ type; int n; struct tr_pattern* next; TYPE_1__ val; } ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ MRB_INT_MAX ; 
 scalar_t__ TR_IN_ORDER ; 
 scalar_t__ TR_RANGE ; 
 scalar_t__ TR_UNINITIALIZED ; 
 int /*<<< orphan*/  mrb_assert (int) ; 

__attribute__((used)) static inline mrb_int
tr_find_character(const struct tr_pattern *pat, const char *pat_str, int ch)
{
  mrb_int ret = -1;
  mrb_int n_sum = 0;
  mrb_int flag_reverse = pat ? pat->flag_reverse : 0;

  while (pat != NULL) {
    if (pat->type == TR_IN_ORDER) {
      int i;
      for (i = 0; i < pat->n; i++) {
	if (pat_str[pat->val.start_pos + i] == ch) ret = n_sum + i;
      }
    }
    else if (pat->type == TR_RANGE) {
      if (pat->val.ch[0] <= ch && ch <= pat->val.ch[1])
        ret = n_sum + ch - pat->val.ch[0];
    }
    else {
      mrb_assert(pat->type == TR_UNINITIALIZED);
    }
    n_sum += pat->n;
    pat = pat->next;
  }

  if (flag_reverse) {
    return (ret < 0) ? MRB_INT_MAX : -1;
  }
  return ret;
}
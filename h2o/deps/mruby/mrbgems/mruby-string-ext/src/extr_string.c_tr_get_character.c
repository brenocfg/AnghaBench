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
struct TYPE_2__ {scalar_t__ start_pos; scalar_t__* ch; } ;
struct tr_pattern {scalar_t__ n; int type; struct tr_pattern* next; TYPE_1__ val; } ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
#define  TR_IN_ORDER 130 
#define  TR_RANGE 129 
#define  TR_UNINITIALIZED 128 

__attribute__((used)) static inline mrb_int
tr_get_character(const struct tr_pattern *pat, const char *pat_str, mrb_int n_th)
{
  mrb_int n_sum = 0;

  while (pat != NULL) {
    if (n_th < (n_sum + pat->n)) {
      mrb_int i = (n_th - n_sum);

      switch (pat->type) {
      case TR_IN_ORDER:
        return pat_str[pat->val.start_pos + i];
      case TR_RANGE:
        return pat->val.ch[0]+i;
      case TR_UNINITIALIZED:
        return -1;
      }
    }
    if (pat->next == NULL) {
      switch (pat->type) {
      case TR_IN_ORDER:
        return pat_str[pat->val.start_pos + pat->n - 1];
      case TR_RANGE:
        return pat->val.ch[1];
      case TR_UNINITIALIZED:
        return -1;
      }
    }
    n_sum += pat->n;
    pat = pat->next;
  }

  return -1;
}
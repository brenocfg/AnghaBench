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
struct value_data {int fields_mask; int zero_mask; int* data; } ;

/* Variables and functions */
 int MAX_EXTRA_MASK ; 
 struct value_data* alloc_value_data (int) ; 
 int /*<<< orphan*/  free_value_data (struct value_data*) ; 

__attribute__((used)) static struct value_data *merge_delayed_values (struct value_data *S, struct value_data *V, int do_mask, int has_zero_mask) {
  int i;
  struct value_data *W;
  int *S_extra, *V_extra, *W_extra;

  do_mask &= V->fields_mask;
  if ((do_mask | S->fields_mask) != S->fields_mask) {
    W = alloc_value_data (do_mask | S->fields_mask);
  } else {
    W = S;
  }
  if (has_zero_mask) {
    W->zero_mask = (do_mask & V->zero_mask) | S->zero_mask;
  } else {
    W->zero_mask = S->zero_mask;
  }

  W_extra = W->data;
  S_extra = S->data;
  V_extra = V->data;

  for (i = 1; i < MAX_EXTRA_MASK; i <<= 1) {
    if (do_mask & i) {
      if ((V->zero_mask & i) || !(S->fields_mask & i)) {
        if (i < 256) {
          *W_extra++ = *V_extra;
        } else {
          *(long long *) W_extra = *(long long *) V_extra;
          W_extra += 2;
        }
      } else {
        if (i < 256) {
          *W_extra++ = *V_extra + *S_extra;
        } else {
          *(long long *) W_extra = *(long long *) V_extra + *(long long *) S_extra;
          W_extra += 2;
        }
      }
    } else if (S->fields_mask & i) {
      if (i < 256) {
        *W_extra++ = *S_extra;
      } else {
        *(long long *) W_extra = *(long long *) S_extra;
        W_extra += 2;
      }
    }

    if (S->fields_mask & i) {
      S_extra += i < 256 ? 1 : 2;
    }

    if (V->fields_mask & i) {
      V_extra += i < 256 ? 1 : 2;
    }
  }
  if (W != S) {
    free_value_data (S);
  }

  return W;
}
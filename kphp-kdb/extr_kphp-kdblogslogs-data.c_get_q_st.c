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
struct TYPE_2__ {long long* std_val; } ;

/* Variables and functions */
 int FN ; 
 int /*<<< orphan*/  QDEC (int) ; 
 TYPE_1__** eq ; 
 scalar_t__ eq_n ; 
 int eq_r ; 
 int* map_int_int_get (int /*<<< orphan*/ *,long long) ; 
 int* map_ll_int_get (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/ * q_st_int ; 
 int /*<<< orphan*/ * q_st_ll ; 
 scalar_t__* std_t ; 

inline int get_q_st (int qid, long long val) {
  if (qid == -1 && eq_n) {
    int t = eq_r;
    QDEC(t);
    return t;
  }

  if (0 <= qid && qid < FN) {
    if (std_t[qid] == 0) {
      int *t = map_int_int_get (&q_st_int[qid], val);
      if (t != NULL && eq[*t] != NULL && eq[*t]->std_val[qid] == val) {
        return *t;
      }
    } else {
      int *t = map_ll_int_get (&q_st_ll[qid], val);
      if (t != NULL && eq[*t] != NULL && (*(long long *)&eq[*t]->std_val[qid]) == val) {
        return *t;
      }
    }
  }

  return -1;
}
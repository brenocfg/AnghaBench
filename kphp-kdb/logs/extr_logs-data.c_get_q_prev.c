#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* q_prev; int timestamp; scalar_t__* std_val; } ;
typedef  TYPE_1__ event ;

/* Variables and functions */
 int /*<<< orphan*/  QDEC (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__** eq ; 
 int eq_l ; 
 int* std_t ; 

inline int get_q_prev (int i, int qid) {
  if (qid == -1) {
    if (i == eq_l) {
      return -1;
    }
    QDEC (i);
    return i;
  }

  event *eqi = eq[i];
  assert (eqi != NULL);
  int ni = eqi->q_prev[qid];
  event *eqni = eq[ni];

  //TODO why we need to compare std_val?
  if (eqni != NULL && eqi->timestamp >= eqni->timestamp - 3601) {
    if (std_t[qid] == 0 && eqi->std_val[qid] == eqni->std_val[qid]) {
      return ni;
    }
    if (std_t[qid] == 1 && *(long long *)&eqi->std_val[qid] == *(long long *)&eqni->std_val[qid]) {
      return ni;
    }
  }
  return -1;
}
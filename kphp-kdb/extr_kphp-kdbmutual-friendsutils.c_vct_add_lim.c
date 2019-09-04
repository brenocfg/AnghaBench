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
struct TYPE_3__ {int mx; int n; int* mem; int rn; } ;
typedef  TYPE_1__ vector ;

/* Variables and functions */
 int* qrealloc (int*,int,int) ; 
 int rand () ; 

void vct_add_lim (vector *v, int x, int lim)  {
  if (v->mx == v->n && v->mx != lim) {
    int new_len = v->mx * 2;
    if (new_len > lim) {
      new_len = lim;
    }
    v->mem = qrealloc (v->mem, sizeof (int) * new_len, sizeof (int) * v->mx);
    v->mx = new_len;
  }

  v->rn++;
  if (v->n < lim) {
    v->mem[v->n++] = x;
  } else {
    int i = rand() % v->rn;
    if (i < v->n) {
      v->mem[i] = x;
    }
  }
}
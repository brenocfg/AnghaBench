#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct union_iterator {long cnt; TYPE_1__** H; } ;
typedef  TYPE_1__* iterator_t ;
struct TYPE_4__ {int pos; int /*<<< orphan*/  jump_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  multiple_union_jump_to ; 

iterator_t build_multiple_union_iterator (iterator_t I) {
  struct union_iterator *IU = (struct union_iterator *) I;
  long N = IU->cnt, k;

  //  fprintf (stderr, "building heap for multiple union iterator of size %ld\n", N);

  I->jump_to = multiple_union_jump_to;
  for (k = N >> 1; k >= 1; k--) {
    iterator_t A = IU->H[k];
    int x = A->pos;
    long i = k;
    while (1) {
      long j = i << 1;
      if (j > N) {
	break;
      }
      if (j < N && IU->H[j]->pos > IU->H[j + 1]->pos) {
	++j;
      }
      if (x <= IU->H[j]->pos) {
	break;
      }
      IU->H[i] = IU->H[j];
      i = j;
    }
    IU->H[i] = A;
  }
  I->pos = IU->H[1]->pos;
  return I;
}
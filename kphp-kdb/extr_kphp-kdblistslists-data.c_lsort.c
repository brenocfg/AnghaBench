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
struct TYPE_3__ {int /*<<< orphan*/  list_id; } ;
typedef  TYPE_1__ list_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 scalar_t__ list_id_less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lsort (list_t **A, int b) {
  if (b <= 0) {
    return;
  }
  int i = 0, j = b;
  list_id_t h = A[b >> 1]->list_id; 
  list_t *t;
  do {
    while (list_id_less (A[i]->list_id, h)) {
      i++;
    }
    while (list_id_less (h, A[j]->list_id)) {
      j--;
    }
    if (i <= j) {
      t = A[i];
      A[i] = A[j];
      A[j] = t;
      i++;
      j--;
    }
  } while (i <= j);
  lsort (A, j);
  lsort (A + i, b - i);
}
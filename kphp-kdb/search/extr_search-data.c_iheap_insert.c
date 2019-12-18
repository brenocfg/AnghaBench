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
struct TYPE_4__ {long long item_id; int /*<<< orphan*/  cur; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 TYPE_1__** H ; 
 int HC ; 
 int MAX_WORDS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void iheap_insert (iheap_en_t *A) {
  int i, j;
  long long item_id = A->item_id;
  assert (HC < MAX_WORDS);
  if (!A->cur) { return; }
  i = ++HC;
  while (i > 1) {
    j = (i >> 1);
    if (H[j]->item_id <= item_id) {
      break;
    }
    H[i] = H[j];
    i = j;
  }
  H[i] = A;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ word; TYPE_1__* item; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_8__ {scalar_t__ word; } ;
typedef  TYPE_3__ iheap_en_t ;
struct TYPE_6__ {long long item_id; } ;

/* Variables and functions */

__attribute__((used)) static inline int ihe_sgn_ext (tree_t *T, iheap_en_t *A, long long item_id) {
  if (T->word < A->word) {
    return -2;
  }
  if (T->word > A->word) {
    return 2;
  }
  if (T->item->item_id < item_id) {
    return -1;
  }
  if (T->item->item_id > item_id) {
    return 1;
  }
  return 0;
}
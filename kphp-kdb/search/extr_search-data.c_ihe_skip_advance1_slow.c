#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* cur1; } ;
typedef  TYPE_2__ iheap_en_t ;
struct TYPE_5__ {long long item_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ihe_advance1_noload (TYPE_2__*) ; 

__attribute__((used)) static void ihe_skip_advance1_slow (iheap_en_t *A, long long item_id) {
  while (A->cur1->item_id < item_id) {
    if (!ihe_advance1_noload (A)) {
      break;
    }
  }
}
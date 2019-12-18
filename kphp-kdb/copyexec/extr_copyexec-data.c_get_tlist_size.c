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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ transaction_t ;
typedef  TYPE_1__ tlist_t ;

/* Variables and functions */

__attribute__((used)) static int get_tlist_size (tlist_t *L) {
  int r = 0;
  transaction_t *T;
  for (T = L->next; T != L; T = T->next) {
    r++;
  }
  return r;
}
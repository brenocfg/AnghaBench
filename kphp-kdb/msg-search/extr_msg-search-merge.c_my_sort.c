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
struct TYPE_3__ {int user_id; } ;
typedef  TYPE_1__ userlist_entry_t ;

/* Variables and functions */
 TYPE_1__** MetaP ; 

__attribute__((used)) static void my_sort (int a, int b) {
  userlist_entry_t *t;
  int h, i, j;
  if (a >= b) return;
  i = a;  j = b;
  h = MetaP[(a+b)>>1]->user_id;
  do {
    while (MetaP[i]->user_id < h) i++;
    while (MetaP[j]->user_id > h) j--;
    if (i <= j) {
      t = MetaP[i];  MetaP[i++] = MetaP[j];  MetaP[j--] = t;
    }
  } while (i <= j);
  my_sort (a, j);
  my_sort (i, b);
}
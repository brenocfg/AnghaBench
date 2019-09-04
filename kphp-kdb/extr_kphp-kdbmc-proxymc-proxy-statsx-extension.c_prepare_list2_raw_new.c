#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  comparel ; 
 int /*<<< orphan*/  comparer ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 

void prepare_list2_raw_new (int *data, int num) {
  assert (*data <= num);
  qsort (data + 1, *data, 8, comparel);
  int i;
  int cl = 0;
  for (i = 0; i < *data; i++) {
    if (i == 0 || data[2 * i + 1] != data[2 * i - 1]) {
      data[2 * cl + 1] = data[2 * i + 1];
      data[2 * cl + 2] = data[2 * i + 2];
      cl ++;
    } else {
      data[2 * cl] += data[2 * i + 2];
    }
  }
  *data = cl;
  qsort (data + 1, *data, 8, comparer);
}
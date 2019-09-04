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
struct gather_entry {int res_read; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * R ; 

__attribute__((used)) static void gather_sum_res (struct gather_entry *GE, int limit) {
  int cnt = (GE->res_read >> 2) - 1;
  int *ptr = GE->data;
  int i;

  if (cnt > limit) { cnt = limit; }
  for (i = 0; i < cnt; i++) {
    R[i] += *ptr++;
  }
}
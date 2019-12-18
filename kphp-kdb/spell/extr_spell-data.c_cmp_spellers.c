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
struct speller {long double** stat; } ;

/* Variables and functions */
 size_t sort_idx ; 

__attribute__((used)) static int cmp_spellers (const void *a, const void *b) {
  const struct speller **x = (const struct speller **) a, **y = (const struct speller **) b;
  long double u = (*x)->stat[sort_idx][0];
  u *= (*y)->stat[sort_idx][1];
  long double v = (*y)->stat[sort_idx][0];
  v *= (*x)->stat[sort_idx][1];
  if (u > v) {
    return -1;
  }
  if (u < v) {
    return 1;
  }
  return 0;
}
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
struct pair_hostid_result {unsigned int result; } ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct pair_hostid_result*,struct pair_hostid_result*,int) ; 

__attribute__((used)) static void filter_pairs_hostid_result (struct pair_hostid_result *a, int *k, unsigned result_or, unsigned result_and) {
  int i, n = 0;
  for (i = 0; i < (*k); i++) {
    if ((a[i].result & result_and) == result_or) {
      if (n < i) {
        memcpy (&a[n], &a[i], sizeof (a[0]));
      }
      n++;
    }
  }
  *k = n;
}
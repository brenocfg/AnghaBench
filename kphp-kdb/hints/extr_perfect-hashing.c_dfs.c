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
 int* di ; 
 int* ne ; 
 int* st ; 
 int* va ; 
 int* was ; 

int dfs (int v, int p, int d) {
  was[v] = 1;
  di[v] = d;
  int i;
  for (i = st[v]; i != -1; i = ne[i]) {
    if (va[i] != p) {
      if (was[va[i]] || !dfs (va[i], v, d + 1)) {
        return 0;
      }
    }
  }
  return 1;
}
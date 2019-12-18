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
 int* KA ; 
 int* KB ; 
 int KN ; 
 char* KS ; 

int aho_search (char *str) {
  int q = 1, m = 0;
  char t;
  
  while ((t = *str) != 0) {
    while (t != KS[q]) {
      q = KA[q];
      if (!q) {
        break;
      }
    }
    m |= KB[++q];
    ++str;
  } 
  return m == (1 << KN) - 1;
  //return m;
}
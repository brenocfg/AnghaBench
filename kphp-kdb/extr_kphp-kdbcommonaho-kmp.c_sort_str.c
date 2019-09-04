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
 int* L ; 
 char** S ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void sort_str (int a, int b) {
  if (a >= b) {
    return;
  }
  int i = a, j = b, q;
  char *h = S[(a + b) >> 1], *t;

  do {
    while (strcmp (S[i], h) < 0) { ++i; }
    while (strcmp (h, S[j]) < 0) { --j; }
    if (i <= j) {
      t = S[i]; S[i] = S[j]; S[j] = t;
      q = L[i]; L[i++] = L[j]; L[j--] = q;
    }
  } while (i <= j);
  sort_str (a, j);
  sort_str (i, b);
}
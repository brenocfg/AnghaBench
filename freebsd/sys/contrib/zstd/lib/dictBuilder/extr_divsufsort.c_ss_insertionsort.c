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
 int ss_compare (unsigned char const*,int const*,int const*,int) ; 

__attribute__((used)) static
void
ss_insertionsort(const unsigned char *T, const int *PA,
                 int *first, int *last, int depth) {
  int *i, *j;
  int t;
  int r;

  for(i = last - 2; first <= i; --i) {
    for(t = *i, j = i + 1; 0 < (r = ss_compare(T, PA + t, PA + *j, depth));) {
      do { *(j - 1) = *j; } while((++j < last) && (*j < 0));
      if(last <= j) { break; }
    }
    if(r == 0) { *j = ~*j; }
    *(j - 1) = t;
  }
}
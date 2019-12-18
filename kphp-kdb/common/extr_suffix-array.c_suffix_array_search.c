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
struct TYPE_4__ {int n; int* p; unsigned char* y; } ;
typedef  TYPE_1__ suffix_array_t ;

/* Variables and functions */
 int get_lcp (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,unsigned char*,int,int,int,int,int const,int const) ; 

int suffix_array_search (suffix_array_t *A, unsigned char *x, int m, int *common_length) {
  const int n = A->n;
  int d = -1, ld = 0;
  int f = n, lf = 0;
  while (d + 1 < f) {
    int i = (d + f) >> 1;
    const int lcp_di = get_lcp (A, d, i), lcp_if = get_lcp (A, i, f);
    vkprintf (3, "suffix_array_search (%.*s), d = %d, ld = %d, f = %d, lf = %d, lcp_di = %d, lcp_if = %d\n", m, x, d, ld, f, lf, lcp_di, lcp_if);    
    if (ld <= lcp_if && lcp_if < lf) {
      d = i;
      ld = lcp_if;
    } else if (ld <= lf && lf < lcp_if) {
      f = i;
    } else if (lf <= lcp_di && lcp_di < ld) {
      f = i;
      lf = lcp_di;
    } else if (lf <= ld && ld < lcp_di) {
      d = i;
    } else {
      const int li = n - A->p[i];
      int l = (ld >= lf) ? ld : lf, o;
      int max_o = li;
      if (max_o > m) { 
        max_o = m; 
      }
      max_o -= l;
      unsigned char *s = x + l, *t = A->y + (A->p[i] + l);
      for (o = 0; o < max_o && *s == *t; o++, s++, t++) {}
      l += o;
      if (l == m && l == li) {
        *common_length = m;
        return A->p[i];
      } else if (l == li || (l != m && *t < *s)) {
        d = i;
        ld = l;
      } else {
        f = i;
        lf = l;
      }
    }
  }
  if (ld >= lf) {
    *common_length = ld;
    return d >= 0 ? A->p[d] : -1;
  }
  *common_length = lf;
  return f < n ? A->p[f] : -1;
}
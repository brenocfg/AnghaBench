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
struct fcb_table_entry {int i; int p; } ;
typedef  int /*<<< orphan*/  T ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct fcb_table_entry* calloc (int,int) ; 
 int /*<<< orphan*/  cmp_fcb_table_entry ; 
 int /*<<< orphan*/  free (struct fcb_table_entry*) ; 
 unsigned int gf32_matrix_times (unsigned int*,unsigned int) ; 
 unsigned int gf32_pow (int,int) ; 
 unsigned int gf32_shl (unsigned int,int) ; 
 int /*<<< orphan*/  qsort (struct fcb_table_entry*,int,int,int /*<<< orphan*/ ) ; 
 unsigned int revbin (unsigned int) ; 
 scalar_t__ sqrt (int) ; 
 int xmult (int) ; 

__attribute__((used)) static int find_corrupted_bit (int size, unsigned d) {
  int i, j;
  size += 4;
  d = revbin (d);
  int n = size << 3;
  int r = (int) (sqrt (n) + 0.5);
//  vkprintf (3, "n = %d, r = %d\n", n, r);
  struct fcb_table_entry *T = calloc (r, sizeof (struct fcb_table_entry));
  assert (T != NULL);
  T[0].i = 0;
  T[0].p = 1;
  for (i = 1; i < r; i++) {
    T[i].i = i;
    T[i].p = xmult (T[i-1].p);
  }
  assert (xmult (0x82608EDB) == 1);
  qsort (T, r, sizeof (T[0]), cmp_fcb_table_entry);
  unsigned q = gf32_pow (0x82608EDB, r);

  unsigned A[32];
  for (i = 0; i < 32; i++) {
    A[i] = gf32_shl (q, i);
  }

  unsigned x = d;
  int max_j = n / r, res = -1;
  for (j = 0; j <= max_j; j++) {
    int a = -1, b = r;
    while (b - a > 1) {
      int c = ((a + b) >> 1);
      if (T[c].p <= x) { a = c; } else { b = c; }
    }
    if (a >= 0 && T[a].p == x) {
      res = T[a].i + r * j;
      break;
    }
    x = gf32_matrix_times (A, x);
  }
  free (T);
  return res;
}
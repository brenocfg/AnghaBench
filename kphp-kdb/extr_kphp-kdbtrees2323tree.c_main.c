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
 int /*<<< orphan*/  T ; 
 int* arr ; 
 int check (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  count (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  dump (int /*<<< orphan*/ ) ; 
 int ld ; 
 int lp ; 
 int nd ; 
 int np ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  scanf (char*,int*) ; 
 int* sort (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tree23_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tree23_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tree23_lookup (int /*<<< orphan*/ ,int) ; 

int main () {
  int n, t, p, i, j;
  int lc = 0, nc = 0 , cc = 0;
  int *tmp;
  scanf ("%d", &n);
  for (i = 0; i < n; i++) {
    scanf ("%d", &t);
    switch (t) {
      case 1:
        scanf ("%d", &p);
        if (!tree23_lookup (T, p))
          tree23_insert (&T, p);
        break;
      case 2:
        scanf ("%d", &p);
        puts (tree23_lookup (T, p)?"YES":"NO");
        break;
      case 3:
        scanf ("%d", &p);
        tmp = sort (T, arr);
        p = tmp - arr;
        for (j = 0; j < p; j++)
          printf ("%d%c", arr[j], '\n');
        break;
      case 4:
        scanf ("%d", &p);
        if (tree23_lookup (T, p))
          tree23_delete (&T, p);
        break;
    }
    //dump (T);
    if (check (T, -1000000000, 1000000000) < 0) printf ("BAD TREE\n");
  }
  printf ("%d\n", check (T, -1000000000, 1000000000));
  dump (T);
  tmp = sort (T, arr);
  p = tmp - arr;
  for (j = 0; j < p; j++)
    printf ("%d%c", arr[j], '\n');
  count (T, &lc, &nc, &cc);
  printf ("leaves allocated %d\nnodes allocated %d\nleaves freed %d\nnodes freed %d\nleaves current %d\nnodes current %d\n", lp, np, ld, nd, lp - ld, np - nd);
  printf ("leaves in tree %d\nnodes in tree %d\nnumbers in tree %d\n", lc, nc, cc);
}
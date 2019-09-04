#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int extra_words; } ;

/* Variables and functions */
 TYPE_1__ Root ; 
 int* arr ; 
 int check (TYPE_1__*) ; 
 int /*<<< orphan*/  count (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  dump (TYPE_1__*) ; 
 int ld ; 
 int lp ; 
 int nd ; 
 int np ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  scanf (char*,int*) ; 
 int* sort (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  tree23_delete (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tree23_insert (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  tree23_lookup (TYPE_1__*,int) ; 

int main (int argc, const char *argv[]) {
  int n, t, p, i, j;
  int counters[3], extra[4];
  int *tmp;
  if (argc >= 2 && !strcmp (argv[1], "-e")) {
    Root.extra_words = 1;
  }
  scanf ("%d", &n);
  for (i = 0; i < n; i++) {
    scanf ("%d", &t);
    switch (t) {
      case 1:
        scanf ("%d", &p);
        if (!tree23_lookup (&Root, p)) {
          extra[0] = p+3;
          tree23_insert (&Root, p, extra);
        }
        break;
      case 2:
        scanf ("%d", &p);
        puts (tree23_lookup (&Root, p)?"YES":"NO");
        break;
      case 3:
        scanf ("%d", &p);
        tmp = sort (&Root, arr);
        p = tmp - arr;
        for (j = 0; j < p; j++)
          printf ("%d%c", arr[j], '\n');
        break;
      case 4:
        scanf ("%d", &p);
        if (tree23_lookup (&Root, p))
          tree23_delete (&Root, p);
        break;
    }
    //dump (T);
    if (check (&Root) < 0) printf ("BAD TREE\n");
  }
  printf ("%d\n", check (&Root));
  dump (&Root);
  tmp = sort (&Root, arr);
  p = tmp - arr;
  for (j = 0; j < p; j++)
    printf ("%d%c", arr[j], '\n');
  count (&Root, counters);
  printf ("leaves allocated %d\nnodes allocated %d\nleaves freed %d\nnodes freed %d\nleaves current %d\nnodes current %d\n", lp, np, ld, nd, lp - ld, np - nd);
  printf ("leaves in tree %d\nnodes in tree %d\nnumbers in tree %d\n", counters[1], counters[2], counters[0]);
  return 0;
}
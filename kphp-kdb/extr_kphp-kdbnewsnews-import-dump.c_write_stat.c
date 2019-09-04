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
 int MAXUSERS ; 
 size_t* a ; 
 int* b ; 
 int* c ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int log_split_mod ; 
 int /*<<< orphan*/  stderr ; 

void write_stat (void) {
  int i;
  int max = 0;
  for (i = 0; i < MAXUSERS; i++)  {
    b[a[i]] ++;
    if (a[i] > max) max = a[i];
  }
  double mean = 0;
  int cou = 0;
  for (i = 1; i <= max; i++) {
    mean += i * b[i];
    cou += b[i];
  }
  mean /= cou;
  fprintf (stderr, "mean bookmarks number is %lf\n", mean);
  fprintf (stderr, "maximal bookmarks number is %d\n", max);
  fprintf (stderr, "total users number is %d\n", cou);

  int e = 0;
  for (i = 1; i <= 100; i++) {
    e += b[i];
    fprintf (stderr, "number of users with %d bookmarks is %d (with more %d)\n", i, b[i], cou - e);
  }

  int min = 1000000000;
  max = 0;
  mean = 0;
  int mai = -1;
  int mii = -1;
  for (i = 0; i < log_split_mod; i++) {
    if (max < c[i]) {
      max = c[i];
      mai = i;
    }
    if (min > c[i]) {
      min = c[i];
      mii = i;
    }
    mean += c[i];
  }
  mean /= log_split_mod;
  fprintf (stderr, "max items in file %d (file %d)\n", max, mai);
  fprintf (stderr, "min items in file %d (file %d)\n", min, mii);
  fprintf (stderr, "mean items in file %d\n", (int)mean);

  /*fprintf (stderr, "number of items with owner = 0, place = 1 is %d (%lf%%)\n", z[0], z[0]/(double)z[1]*100);
  fprintf (stderr, "(%d,%d,%d,%d,%d)\n", z[20], z[21], z[22], z[23], z[24]);

  max = 0;
  int ii = 0;
  for (i = 0; i < MAXUSERS; i++) {
    if (max < u[i]) {
      max = u[i];
      ii = i;
    }
  }
  fprintf (stderr, "most rich owner is %d (%d items (%lf%%))\n", ii, max, max / (double)z[1] * 100);*/



}
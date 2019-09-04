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
 int A1 ; 
 int A2 ; 
 int B1 ; 
 int B2 ; 
 int MAX_ANS ; 
 int* a ; 
 int an ; 
 int /*<<< orphan*/  assert (int) ; 
 int* b ; 
 size_t* c ; 
 int* cnt ; 
 int* d ; 
 size_t dn ; 
 int engineN ; 
 scalar_t__* fd ; 
 int h_add (int,int) ; 
 int* h_key ; 
 int /*<<< orphan*/  h_rem (int) ; 
 int* h_val ; 
 scalar_t__ load (int,int,int*) ; 
 int maxn ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_read1 () ; 
 int /*<<< orphan*/  my_read2 () ; 
 int /*<<< orphan*/  my_write (int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ test_mode ; 
 int this_mod ; 
 int un ; 
 int userN ; 

void run (void) {
  int i, j;
  for (j = 0; j <= un && j * engineN + this_mod <= userN; j++) {
    an = 0;
    for (i = 0; i < engineN; i++) {
      if (fd[i] >= 0) {
        an += load (i, j, a + an);
      }
    }
    assert (an < maxn);
    int add;

    dn = 0;

    for (i = 0; i < an; i++) {
      add = (a[i] & 1) * 3 + 1;
      a[i] /= 2;
      d[dn] = h_add (a[i], add);
      if (d[dn] != -1) {
        dn++;
      }
    }

    int curr_f = j * engineN + this_mod;

    while (A1 <= curr_f) {
      if (A1 == curr_f) {
        if (B1 >= 0) {
          h_rem (B1 & ((1 << 30) - 1));
        }
      }
      if (!my_read1()) {
        break;    	
      }
    }

    while (A2 <= curr_f) {
      if (A2 == curr_f) {
        if (B2 >= 0) {
          h_rem (B2 & ((1 << 30) - 1));
        }
      }
      if (!my_read2()) {
        break;
      }
    }

    int n = 0, mx = 0;

    for (i = 0; i < dn; i++) {
      int j = d[i];
      if (h_val[j]) {
        a[n] = h_key[j];
        b[n] = h_val[j];
        if (mx < b[n]) {
          mx = b[n];
        }
        n++;
      }
      h_key[j] = 0;
      h_val[j] = 0;
    }


    memset (cnt, 0, sizeof (int) * (mx + 1));
    for (i = 0; i < n; i++) {
      cnt[b[i]]++;
    }
    int t = 0;
    for (i = 1; i <= mx; i++) {
      int tt = cnt[i];
      cnt[i] = cnt[i - 1] + t;
      t = tt;
    }

    for (i = 0; i < n; i++) {
      c[cnt[b[i]]++] = i;
    }

    int wn = n;
    if (wn > MAX_ANS) {
      wn = MAX_ANS;
    }

    my_write (&curr_f, sizeof (int));
    my_write (&wn, sizeof (int));
    for (i = 1; i <= wn; i++) {
      my_write (&b[c[n - i]], sizeof (int));
      my_write (&a[c[n - i]], sizeof (int));
    }

    if (test_mode) {
      printf ("%d %d", curr_f, wn);

      for (i = 1; i <= wn; i++) {
        printf (" (%d;%d)", b[c[n - i]], a[c[n - i]]);
      }
      printf ("\n");
    }
  }
}
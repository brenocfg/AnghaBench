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
struct counter {unsigned long long mask_subcnt; int* subcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  zzfree (int*,int) ; 
 scalar_t__ zzmalloc (int) ; 

int packed_subcnt_increment (struct counter *c, int idx, int delta ) {
  int i,j;
  unsigned long long u, w, m = 1;
  int *p;
  if (verbosity >= 4) {
    fprintf(stderr, "packed_subcnt_increment(c = %p, idx = %d, delta = %d)\n", c, idx, delta);
    fprintf(stderr, "c->mask_subcnt = %llx\n", c->mask_subcnt);
  }
  m <<= idx;
  if (m & c->mask_subcnt) {
    u = c->mask_subcnt;
    for (i=0;;i++) {
      w = u & (u - 1);
      if (m == (u ^ w) ) break;
      u = w;
    }
    return ( c->subcnt[i] += delta ) ;
  }
  else {
    u = c->mask_subcnt;
    j = -1;
    for (i=0;u != 0;i++) {
      w = u & (u - 1);
      if (m > (u ^ w)) j = i;
      u = w;
    }    
    p = (int*) zzmalloc(sizeof(int) * (i+1));
    p[j+1] = delta;
    if (i > 0) {
      memcpy(p, c->subcnt, sizeof(int) * (j+1));
      memcpy(p+(j+2), c->subcnt + (j+1), sizeof(int) * (i - (j+1)));
      zzfree(c->subcnt, sizeof(int) * i);
    }
    c->subcnt = p;
    c->mask_subcnt |= m;
    if (verbosity >= 4) {
      fprintf(stderr, "c->subcnt = ");
      for (j=0;j<=i;j++) fprintf (stderr, "%d ", c->subcnt[j]);
      fprintf(stderr, "\n");
    }
    return delta;
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ treap ;
typedef  int* changes ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  trp_debug_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void chg_debug_print (changes x, FILE *f) {
  if ((long)(x) < 0) {
    long t = -(long)(x);
    fprintf (f, " [1] : %+ld\n", (t / 2) * (t & 1 ? +1 : -1));
  } else if (x) {
    if (x[0] < 0) {
      fprintf (f, "[%d] :", x[0]);
      trp_debug_print (((treap *)(x))->root, f);
      fprintf (f, "\n");
//      fprintf (f, " [?] : LAZHA\n");
    } else {
      fprintf (f, " [%d] :", x[0]);
      int i;
      for (i = 1; i <= x[0]; i++) {
        fprintf (f, " %+d", (x[i] / 2) * (x[i] & 1 ? +1 : -1));
      }
      fprintf (f, "\n");
    }
  }
}
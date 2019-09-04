#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_5__ {int a; struct TYPE_5__* xl; struct TYPE_5__* xr; } ;

/* Variables and functions */

void dl_prm_rev_split (dl_prm_ptr v, int x, dl_prm_ptr *a, dl_prm_ptr *b) {
  while (v != NULL) {
    if (v->a < x) {
      *a = v;
      a = &v->xr;
      v = v->xr;
    } else {
      *b = v;
      b = &v->xl;
      v = v->xl;
    }
  }
  *a = *b = NULL;
}
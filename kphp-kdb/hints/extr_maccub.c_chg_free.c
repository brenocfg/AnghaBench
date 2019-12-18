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

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int*,int) ; 
 int /*<<< orphan*/  trp_free (int /*<<< orphan*/ ) ; 

void chg_free (changes *_x) {
  changes x = *_x;

#ifdef __x86_64__
  if ((long)(x) < 0) {
  } else
#endif
  if (x) {
    if (x[0] < 0) {
      trp_free (((treap *)x)->root);
      dl_free (x, sizeof (treap));
    } else {
      dl_free (x, sizeof (int) * (x[0] + 1));
    }
  }

  *_x = NULL;
}
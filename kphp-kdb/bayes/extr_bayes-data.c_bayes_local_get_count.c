#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ll ;
struct TYPE_3__ {int spam; int ham; } ;
struct TYPE_4__ {scalar_t__ h; TYPE_1__ val; } ;
typedef  TYPE_2__ entry_t ;

/* Variables and functions */
 int SPAM ; 

int bayes_local_get_count (char *b, ll word, int type) {
  int n = ((int *)b)[0];
  entry_t *a = (entry_t *)(b + sizeof (int));

  if (n == 0) {
    return 0;
  }

  int l = 0, r = n;
  while (l + 1 < r) {
    int m = l + ((r - l) >> 1);
    if (a[m].h > word) {
      r = m;
    } else {
      l = m;
    }
  }

  if (a[l].h != word)
    return 0;

  if (type == SPAM) {
    return a[l].val.spam;
  } else {
    return a[l].val.ham;
  }
}
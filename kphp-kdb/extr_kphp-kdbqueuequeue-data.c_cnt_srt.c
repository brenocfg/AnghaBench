#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  was ;
struct TYPE_4__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ pli ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int dl_abs (int /*<<< orphan*/ ) ; 
 int engine_n ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void cnt_srt (pli *a, int n, pli *b) {
  static int was[10001] = {0},
             num[10001] = {0},
             st[10001] = {0},
             vn = 0, id = 0;

  assert (0 < engine_n && engine_n <= 10000);

  if (++id == 0) {
    memset (was, 0, sizeof (was));
    id = 1;
  }

  int i;
  vn = 0;
  st[0] = 0;
  for (i = 0; i < n; i++) {
    int x = dl_abs (a[i].x) % engine_n;
    if (was[x] != id) {
      num[x] = vn;
      was[x] = id;
      vn++;
      st[vn] = 0;
    }

    st[num[x] + 1]++;
  }
  for (i = 0; i < vn; i++) {
    st[i + 1] += st[i];
  }
  for (i = 0; i < n; i++) {
    b[st[num[dl_abs (a[i].x) % engine_n]]++] = a[i];
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int const metafile_len; scalar_t__ metafile; int /*<<< orphan*/  new_exceptions; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int chg_has (int /*<<< orphan*/ ,int) ; 

int user_has_exception (user *u, int val) {
  int i;

  if ( (i = chg_has (u->new_exceptions, val)) ) {
      return i > 0;
  }

  int *a = (int *)u->metafile;
  if (a == NULL) {
    return 0;
  }

  const int int_size = (int)sizeof (int);
  assert (u->metafile_len >= int_size);
  int n = a[0];

  assert (u->metafile_len >= int_size * (1 + n));
  assert (u->metafile_len <= int_size * (1 + n));
  if (n <= 5) {
    for (i = 1; i <= n; i++) {
      if (a[i] == val) {
        return 1;
      }
    }
    return 0;
  } else {
    int l = 1, r = n + 1, c;
    while (l + 1 < r) {
      c = (l + r) / 2;
      if (a[c] >= val) {
        l = c;
      } else {
        r = c;
      }
    }
    return a[l] == val;
  }
}
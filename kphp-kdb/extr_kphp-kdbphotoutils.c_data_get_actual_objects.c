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
struct TYPE_4__ {int /*<<< orphan*/  prm; } ;
typedef  TYPE_1__ data ;
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 int PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int data_get_actual_object (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slice ; 

int data_get_actual_objects (data *d, actual_object *o, int mx) {
  static int p[1000];
  int n = PERM (slice, &d->prm, p, 1000, 0);
  assert (n < 1000);
  if (n > mx) {
    n = mx;
  }
  int i;
  for (i = 0; i < n; i++) {
    assert (data_get_actual_object (d, p[i], &o[i]) > -1);
  }

  return n;
}
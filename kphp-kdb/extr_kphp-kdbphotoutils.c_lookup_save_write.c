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
 int /*<<< orphan*/  WRITE_INT (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

int lookup_save_write (int *x, int *y, int n, char *s, int sn) {
  char *st = s;

  assert (sn >= (int)sizeof (int));
  WRITE_INT (s, n);
  sn -= sizeof (int);

  assert (sn >= (int)sizeof (int) * 2 * n);
  int d = sizeof (int) * n;
  memcpy (s, x, d);
  s += d;
  memcpy (s, y, d);
  s += d;

  return s - st;
}
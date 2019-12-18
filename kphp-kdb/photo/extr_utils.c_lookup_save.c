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
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int*,size_t) ; 
 int* dl_malloc (size_t) ; 
 int lookup_save_expected_len (int /*<<< orphan*/ *) ; 
 int lookup_save_prepare (int /*<<< orphan*/ *,int*,int*,int,int) ; 
 int lookup_save_write (int*,int*,int,char*,int) ; 

int lookup_save (lookup *l, char *buf, int sn, int none) {
  char *s = buf;

  int mx_n = lookup_save_expected_len (l);
  size_t xy_size = sizeof (int) * mx_n;
  int *x = dl_malloc (xy_size),
     *y = dl_malloc (xy_size);

  int n = lookup_save_prepare (l, x, y, mx_n, none);

  int sdv = lookup_save_write (x, y, n, s, sn);
  s += sdv;
  sn -= sdv;

  dl_free (x, xy_size);
  dl_free (y, xy_size);

  return s - buf;
}
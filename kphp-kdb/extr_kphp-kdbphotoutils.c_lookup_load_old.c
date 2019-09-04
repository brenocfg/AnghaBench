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
struct TYPE_3__ {int n; int* x; int* y; } ;
typedef  TYPE_1__ lookup ;

/* Variables and functions */

size_t lookup_load_old (lookup *l, char *metafile, int max_metafile_len, int n) {
  size_t size = 0;

#ifdef LOOKUP_CNT
    if (l->n == -2) {
      l->real_n += n;
    }
#endif

  l->n = n;

  size = sizeof (int) * l->n * 2;
//  assert (max_metafile_len >= (int)size);

  l->x = (int *)metafile;
  l->y = (int *)metafile + l->n;
  return size;
}
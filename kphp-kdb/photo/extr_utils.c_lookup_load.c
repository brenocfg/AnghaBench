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
struct TYPE_3__ {int n; int real_n; int* x; int* y; } ;
typedef  TYPE_1__ lookup ;

/* Variables and functions */
 int /*<<< orphan*/  READ_INT (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void lookup_load (lookup *l, char *metafile, int metafile_len) {
  if (metafile != NULL) {
    assert (metafile_len >= (int)sizeof (int));

    int n;
    READ_INT (metafile, n);

#ifdef LOOKUP_CNT
    if (l->n == -2) {
      l->real_n += n;
    }
#endif

    l->n = n;

    assert (metafile_len == (int)sizeof (int) + (int)sizeof (int) * l->n * 2);
  } else {
    l->n = 0;
  }
  l->x = (int *)metafile;
  l->y = (int *)metafile + l->n;
}
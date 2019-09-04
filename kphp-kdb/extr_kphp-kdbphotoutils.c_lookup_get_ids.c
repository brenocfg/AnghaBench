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
struct TYPE_3__ {int n; int /*<<< orphan*/  new_v; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ lookup ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free (int*,size_t) ; 
 int* dl_malloc (size_t) ; 
 int /*<<< orphan*/ * map_int_int_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int map_int_int_pairs (int /*<<< orphan*/ *,int*,int*,int) ; 
 int map_int_int_used (int /*<<< orphan*/ *) ; 

int lookup_get_ids (lookup *l, int *v, int mx) {
  int *st = v;
  int i;
  for (i = 0; i < l->n; i++) {
    if (map_int_int_get (&l->new_v, l->x[i]) == NULL) {
      if (mx > 0) {
        *v++ = l->x[i];
        mx--;
      }
    }
  }

  int nn = map_int_int_used (&l->new_v);
  if (nn == 0) {
    return v - st;
  }

  size_t ab_size = nn * sizeof (int);
  int *a = dl_malloc (ab_size);
  int *b = dl_malloc (ab_size);

  assert (map_int_int_pairs (&l->new_v, a, b, nn) == nn);
  for (i = 0; i < nn; i++) {
    if (b[i] != -1) {
      if (mx > 0) {
        *v++ = a[i];
        mx--;
      }
    }
  }

  dl_free (a, ab_size);
  dl_free (b, ab_size);

  return v - st;
}
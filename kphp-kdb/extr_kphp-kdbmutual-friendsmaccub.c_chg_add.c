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
typedef  int /*<<< orphan*/  trp_node_ptr ;
struct TYPE_3__ {int size; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ treap ;
typedef  int* changes ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  my_rand () ; 
 int /*<<< orphan*/  qfree (int*,int) ; 
 int* qmalloc (int) ; 
 int* qmalloc0 (int) ; 
 int /*<<< orphan*/  trp_add_or_set (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trp_conv_from_array (int*,int) ; 

void chg_add (changes *_x, int val) {
  assert (val > 0);

  changes x = *_x;

  int *t = 0;
#ifdef __x86_64__
  if ((long)x < 0) {
    if ((long)x == -val) {
      return;
    } else if ((-(long)x) == (val ^ 1)) {
      x = (int *)((long)-val);
    } else {
      int old = -(long)x;
      x = qmalloc  (sizeof (int) * 3);

      assert (x != NULL);

      x[0] = 2;
      if (val < old) {
        x[1] = old;
        x[2] = val;
      } else {
        x[1] = val;
        x[2] = old;
      }
    }
  } else
#endif
  if (x) {
    if (x[0] > 0) {
      int len = x[0], i = 1;
      while (i <= len && (x[i] & -2) > (val & -2)) {
        i++;
      }
      if (i <= len && x[i] == val) {
        return;
      } else if (i <= len && x[i] == (val ^ 1)) {
        x[i] = val;
        return;
      }
      int j = i;
      while (j <= len && x[j]) {
        j++;
      }

//      fprintf (stderr, "i = %d, j = %d\n", i, j);

      if (j > len) {
        if (len == 8) {
          trp_node_ptr root = trp_conv_from_array ((int *)x + 1, len);
          qfree (x, sizeof (int) * (len + 1));
          x = qmalloc (sizeof (treap));
          //x[0] = -len;

          ((treap *)(x))->size = -len;
          ((treap *)(x))->root = root;
        } else {
          t = qmalloc0 (sizeof (int) * (len * 2 + 1));

          assert (t != NULL);

          t[0] = len * 2;
          memcpy (t + 1, x + 1, sizeof (int) * len);
          qfree (x, sizeof (int) * (len + 1));
          len *= 2;
          x = t;
        }
      }

      if (j <= len) {
        while (j != i) {
          x[j] = x[j - 1];
          j--;
        }
        x[j] = val;
      }
    }

    if (x[0] < 0) {
      trp_add_or_set ((treap *)(x), val, my_rand());
    }

  } else {
#ifdef __x86_64__
    x = (changes)((long)-val);
#else
    x = qmalloc0 (sizeof (int) * 2);
    x[0] = 1;
    x[1] = val;
#endif
  }

  *_x = x;
}
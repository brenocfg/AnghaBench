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
typedef  int /*<<< orphan*/  bcode_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int bcode_iter_get_val (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcode_iter_init (int /*<<< orphan*/ *,unsigned char*,int,int,int) ; 

int bcode_encode_list (int *P, int len, int tot_items, unsigned char *res) {
  //assert (len > 0);

  unsigned char *cur = res;

  int k = 0;
  int p = 1;

  while (p <= tot_items) {
    p += p;
    k++;
  }
  int left = 8, i;
  *cur = 0;

  for (i = 0; i < len; i++) {
    int c = P[i];
    int ck = k;

    while (ck > left) {
      ck -= left;
      *cur += (unsigned char)((c >> ck) << (8 - left));
      left = 8;
      *++cur = 0;
    }

    *cur += (unsigned char)((c & ((1 << ck) - 1))  << (8 - left));
    left -= ck;
  }


  bcode_iterator it;
  bcode_iter_init (&it, res, tot_items, (cur - res) + 1, tot_items);
/*  fprintf (stderr, "len = %d, tot_items = %d, k = %d\n", len, tot_items, k);
  for (i = 0; i + res <= cur; i++) {
    fprintf (stderr, "%x ", (int)res[i]);
  }
  fprintf (stderr, "\n");
  for (i = 0; i < len; i++) {
    fprintf (stderr, "%d ", P[i]);
  }
  fprintf (stderr, "\n");*/
  for (i = 0; i < len; i++) {
//    fprintf (stderr, "%d vs %d\n", bcode_iter_get_val (&it, i), P[i]);
    assert (bcode_iter_get_val (&it, i) == P[i]);
  }
  return (cur - res) + 1;
}
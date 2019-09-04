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
typedef  int /*<<< orphan*/  iCode_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  iCode_f (int*,int,int,int /*<<< orphan*/ ,unsigned char**,int*) ; 
 int /*<<< orphan*/  iCode_iter_init (int /*<<< orphan*/ *,unsigned char*,int,int,int) ; 
 int /*<<< orphan*/  iCode_iter_next (int /*<<< orphan*/ *) ; 
 int iCode_iter_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iCode_write (int,unsigned char**,int*,int) ; 

int iCode_encode_list (int *P, int len, int tot_items, unsigned char *res) {
  assert (len > 0);

  unsigned char *st = res;

  int skip = 8;
  res--;
  iCode_write (len - 1, &res, &skip, tot_items);
  iCode_f (P, len, tot_items, 0, &res, &skip);


  int i;
  iCode_iterator it;
  iCode_iter_init (&it, st, tot_items, res - st + 1, tot_items);

//  for (i = 0; i < res - st + 1; i++)
//    fprintf (stderr, "%x%c", (int)st[i], " \n"[i==res-st]);

  for (i = 0; i < len; i++) {
//    fprintf (stderr, "%d vs %d\n", iCode_iter_val (&it), P[i]);
    assert (iCode_iter_val (&it) == P[i]);
    iCode_iter_next (&it);
  }
  assert (iCode_iter_val (&it) == 0);

  return res - st + 1;
}
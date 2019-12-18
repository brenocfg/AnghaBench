#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  list_id_t ;
struct TYPE_2__ {int tot_lists; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLI_ENTRY_LIST_ID (int) ; 
 TYPE_1__ Header ; 
 int list_id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int find_metafile (list_id_t list_id) {
  int l = -1, r = Header.tot_lists;
  int p = -1;
  while (r - l > 1) { // M[l] <= list_id < M[r] 
    int x = (l + r) >> 1;
    //fprintf (stderr, "%d %d %d %d %d\n", l, r, x, list_id, FLI_ENTRY_LIST_ID(x));
    p = list_id_compare (list_id, FLI_ENTRY_LIST_ID(x));
    if (p < 0) {
      r = x;
    } else {
      l = x;
    }
  }
  if (l >= 0 && list_id_equal (list_id, FLI_ENTRY_LIST_ID (l))) {
    return l;
  } else {
    return -1;
  }
}
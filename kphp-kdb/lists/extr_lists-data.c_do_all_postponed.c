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
struct TYPE_2__ {int tot_lists; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLI_ENTRY_LIST_ID (int) ; 
 TYPE_1__ Header ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mark_list_metafile (int /*<<< orphan*/ ) ; 
 int metafile_mode ; 
 scalar_t__* postponed ; 
 scalar_t__ prepare_list_metafile_num (int,int) ; 

void do_all_postponed (void) {
  int i;
  if (!postponed) {
    assert (!Header.tot_lists);
    return;
  }
  assert (postponed);
  for (i = 0; i < Header.tot_lists; i++) {
    //if (postponed[i]) {
    if (postponed[i]) {
      assert (prepare_list_metafile_num (i, -1) >= 0);
    }
    if (postponed[i] && !(metafile_mode & 1)) {
      mark_list_metafile (FLI_ENTRY_LIST_ID (i));
    }
    //}
  }
}
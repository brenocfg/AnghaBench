#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tot_lists; } ;
struct TYPE_3__ {scalar_t__ aio; scalar_t__ data; } ;

/* Variables and functions */
 TYPE_2__ Header ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** metafiles ; 
 int tot_revlist_metafiles ; 

int check_metafile_loaded (int x, int use_aio) {
  assert (0 <= x && x < Header.tot_lists + tot_revlist_metafiles + 1);
  if (metafiles[x] && metafiles[x]->data) {
    if (use_aio == 0) {
      assert (!metafiles[x]->aio);
    }
    if (use_aio < 0 && metafiles[x]->aio) {
      return 0;
    }
    return 1;
  } else {
    return 0;
  }
}
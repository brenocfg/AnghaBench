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
struct TYPE_2__ {scalar_t__ tot_lists; } ;

/* Variables and functions */
 TYPE_1__ Header ; 
 int check_metafile_loaded (scalar_t__,int) ; 

int check_revlist_metafile_loaded (int x, int use_aio) {
  if (x == -1) {
    return 1;
  }
  return check_metafile_loaded (x + Header.tot_lists + 1, use_aio);
}
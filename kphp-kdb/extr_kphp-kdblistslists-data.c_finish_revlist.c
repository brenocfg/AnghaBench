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

/* Variables and functions */
 int /*<<< orphan*/  get_write_pos () ; 
 int /*<<< orphan*/  metafile_crc32 ; 
 int /*<<< orphan*/ * new_revlist_metafiles_crc32 ; 
 int /*<<< orphan*/ * new_revlist_metafiles_offsets ; 
 int new_tot_revlist_metafiles ; 

void finish_revlist (void) {
  new_revlist_metafiles_crc32[new_tot_revlist_metafiles - 1] = metafile_crc32;
  new_revlist_metafiles_offsets[new_tot_revlist_metafiles] = get_write_pos ();
}
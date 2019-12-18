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
 int /*<<< orphan*/  assert (int) ; 
 long long* revlist_metafiles_offsets ; 
 int tot_revlist_metafiles ; 

__attribute__((used)) static inline long long get_revlist_metafile_offset (int p) {
  assert (p >= 0 && p <= tot_revlist_metafiles);
  return revlist_metafiles_offsets[p];
}
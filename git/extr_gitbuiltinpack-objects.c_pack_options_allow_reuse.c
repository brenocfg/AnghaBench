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
 scalar_t__ allow_ofs_delta ; 
 int /*<<< orphan*/  have_non_local_packs ; 
 int /*<<< orphan*/  ignore_packed_keep_in_core ; 
 int /*<<< orphan*/  ignore_packed_keep_on_disk ; 
 int /*<<< orphan*/  incremental ; 
 int /*<<< orphan*/  local ; 
 scalar_t__ pack_to_stdout ; 

__attribute__((used)) static int pack_options_allow_reuse(void)
{
	return pack_to_stdout &&
	       allow_ofs_delta &&
	       !ignore_packed_keep_on_disk &&
	       !ignore_packed_keep_in_core &&
	       (!local || !have_non_local_packs) &&
	       !incremental;
}
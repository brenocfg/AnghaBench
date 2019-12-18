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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_xfer_partial; int /*<<< orphan*/  to_make_corefile_notes; int /*<<< orphan*/  to_find_memory_regions; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  default_xfer_partial ; 
 int /*<<< orphan*/  dummy_find_memory_regions ; 
 int /*<<< orphan*/  dummy_make_corefile_notes ; 
 int /*<<< orphan*/  dummy_stratum ; 
 TYPE_1__ dummy_target ; 
 int /*<<< orphan*/  find_default_attach ; 
 int /*<<< orphan*/  find_default_create_inferior ; 
 int /*<<< orphan*/  normal_pid_to_str ; 

__attribute__((used)) static void
init_dummy_target (void)
{
  dummy_target.to_shortname = "None";
  dummy_target.to_longname = "None";
  dummy_target.to_doc = "";
  dummy_target.to_attach = find_default_attach;
  dummy_target.to_create_inferior = find_default_create_inferior;
  dummy_target.to_pid_to_str = normal_pid_to_str;
  dummy_target.to_stratum = dummy_stratum;
  dummy_target.to_find_memory_regions = dummy_find_memory_regions;
  dummy_target.to_make_corefile_notes = dummy_make_corefile_notes;
  dummy_target.to_xfer_partial = default_xfer_partial;
  dummy_target.to_magic = OPS_MAGIC;
}
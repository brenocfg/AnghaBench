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
typedef  int /*<<< orphan*/  kfs_file_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  antispam_init () ; 
 char* engine_snapshot_name ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_load_time ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int load_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

void init_all (kfs_file_handle_t Index) {
  index_load_time = -get_utime (CLOCK_MONOTONIC);
  bool index_loaded = load_index (Index);
  index_load_time += get_utime (CLOCK_MONOTONIC);

  if (!index_loaded) {
    fprintf (stderr, "fatal: error while loading index file %s\n", engine_snapshot_name);
    exit (1);
  }

  if (verbosity > 0) {
    fprintf (stderr, "load index: done, jump_log_pos=%lld, time %.06lfs\n", jump_log_pos, index_load_time);
  }

  // initialize zmalloc and etc..
  init_dyn_data();

  antispam_init();
}
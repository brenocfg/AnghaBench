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
 int /*<<< orphan*/  binlogpos_filename ; 
 int sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int strlen (char*) ; 
 char* szBinlogpos ; 
 char* work_dir ; 
 int work_dir_length ; 
 int /*<<< orphan*/  zmalloc (int) ; 

__attribute__((used)) static void compute_binlogpos_filename (void) {
  int binlogpos_filename_length = work_dir_length + 1 + strlen (szBinlogpos);
  binlogpos_filename = zmalloc (binlogpos_filename_length + 1);
  assert (sprintf (binlogpos_filename, "%s/%s", work_dir, szBinlogpos) == binlogpos_filename_length);
}
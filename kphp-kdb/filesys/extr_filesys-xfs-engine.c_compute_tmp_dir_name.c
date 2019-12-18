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
 scalar_t__ sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* szTmpDirName ; 
 int /*<<< orphan*/  tmp_dir ; 
 scalar_t__ tmp_dir_length ; 
 char* work_dir ; 
 scalar_t__ work_dir_length ; 
 int /*<<< orphan*/  zmalloc (scalar_t__) ; 

__attribute__((used)) static void compute_tmp_dir_name (void) {
  tmp_dir_length = work_dir_length + 1 + strlen (szTmpDirName);
  tmp_dir = zmalloc (tmp_dir_length + 1);
  assert (sprintf (tmp_dir, "%s/%s", work_dir, szTmpDirName) == tmp_dir_length);
}
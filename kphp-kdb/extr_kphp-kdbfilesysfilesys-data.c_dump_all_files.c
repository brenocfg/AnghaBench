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
 int /*<<< orphan*/ * Root ; 
 int /*<<< orphan*/  rec_dump_all_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dump_all_files (void) {
  if (Root == NULL) {
    return;
  }
  rec_dump_all_files (Root, 0);
}
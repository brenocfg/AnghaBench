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
 int /*<<< orphan*/  binlogpos_filename ; 
 int binlogpos_pos ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlink_binlogpos (void) {
  if (binlogpos_pos >= 0) {
    if (unlink (binlogpos_filename)) {
      kprintf ("unlink (%s) failed. %m\n", binlogpos_filename);
      exit (1);
    }
    binlogpos_pos = -1;
  }
}
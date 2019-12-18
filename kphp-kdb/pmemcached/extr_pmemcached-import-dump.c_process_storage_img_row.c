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
 int /*<<< orphan*/ * S ; 
 int /*<<< orphan*/  do_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nrecords ; 
 size_t si_new_path ; 
 size_t si_old_path ; 

void process_storage_img_row (void) {
  do_store (S[si_old_path], S[si_new_path]);
  nrecords++;
}
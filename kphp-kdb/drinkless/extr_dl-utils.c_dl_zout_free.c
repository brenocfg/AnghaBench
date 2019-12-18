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
typedef  int /*<<< orphan*/  dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  dl_zout_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_zout_free_buffer (int /*<<< orphan*/ *) ; 

void dl_zout_free (dl_zout *f) {
  dl_zout_flush (f); //save for legacy
  dl_zout_free_buffer (f);
}
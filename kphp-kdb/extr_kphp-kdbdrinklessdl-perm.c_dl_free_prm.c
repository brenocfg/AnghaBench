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
typedef  int /*<<< orphan*/  dl_prm_ptr ;
typedef  int /*<<< orphan*/  dl_prm ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int) ; 

void dl_free_prm (dl_prm_ptr v) {
  dl_free (v, sizeof (dl_prm));
}
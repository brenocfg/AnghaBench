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
 int /*<<< orphan*/  tboot_pg_dir ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cr3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void switch_to_tboot_pt(void)
{
	write_cr3(virt_to_phys(tboot_pg_dir));
}
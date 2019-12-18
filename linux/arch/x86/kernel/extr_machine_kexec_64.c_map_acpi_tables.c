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
struct x86_mapping_info {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */

__attribute__((used)) static int map_acpi_tables(struct x86_mapping_info *info, pgd_t *level4p) { return 0; }
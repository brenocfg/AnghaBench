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
struct skd_device {int skcomp_cycle; scalar_t__ skcomp_ix; int /*<<< orphan*/  skcomp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKD_SKCOMP_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skd_reset_skcomp(struct skd_device *skdev)
{
	memset(skdev->skcomp_table, 0, SKD_SKCOMP_SIZE);

	skdev->skcomp_ix = 0;
	skdev->skcomp_cycle = 1;
}
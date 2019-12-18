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
struct tegra_dfll {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ DFLL_OPEN_LOOP ; 

__attribute__((used)) static bool dfll_is_running(struct tegra_dfll *td)
{
	return td->mode >= DFLL_OPEN_LOOP;
}
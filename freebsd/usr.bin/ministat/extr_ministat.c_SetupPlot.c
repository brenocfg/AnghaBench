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
struct plot {int width; int separate_bars; int num_datasets; int min; int max; int /*<<< orphan*/ * bar; int /*<<< orphan*/ * data; scalar_t__ height; } ;

/* Variables and functions */
 struct plot plot ; 

__attribute__((used)) static void
SetupPlot(int width, int separate, int num_datasets)
{
	struct plot *pl;

	pl = &plot;
	pl->width = width;
	pl->height = 0;
	pl->data = NULL;
	pl->bar = NULL;
	pl->separate_bars = separate;
	pl->num_datasets = num_datasets;
	pl->min = 999e99;
	pl->max = -999e99;
}
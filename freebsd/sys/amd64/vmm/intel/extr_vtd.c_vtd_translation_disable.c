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
struct vtdmap {int gsr; scalar_t__ gcr; } ;

/* Variables and functions */
 int VTD_GSR_TES ; 

__attribute__((used)) static void
vtd_translation_disable(struct vtdmap *vtdmap)
{

	vtdmap->gcr = 0;
	while ((vtdmap->gsr & VTD_GSR_TES) != 0)
		;
}
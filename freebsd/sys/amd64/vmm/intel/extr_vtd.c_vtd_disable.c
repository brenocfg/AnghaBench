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
struct vtdmap {int dummy; } ;

/* Variables and functions */
 int drhd_num ; 
 int /*<<< orphan*/  vtd_translation_disable (struct vtdmap*) ; 
 struct vtdmap** vtdmaps ; 

__attribute__((used)) static void
vtd_disable(void)
{
	int i;
	struct vtdmap *vtdmap;

	for (i = 0; i < drhd_num; i++) {
		vtdmap = vtdmaps[i];
		vtd_translation_disable(vtdmap);
	}
}
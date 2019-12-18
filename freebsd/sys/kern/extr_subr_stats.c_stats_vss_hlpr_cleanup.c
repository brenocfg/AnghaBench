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
typedef  int uint32_t ;
struct voistatspec {int /*<<< orphan*/ * iv; scalar_t__ hlpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stats_free (void*) ; 

void
stats_vss_hlpr_cleanup(uint32_t nvss, struct voistatspec *vss)
{
	int i;

	for (i = nvss - 1; i >= 0; i--) {
		if (vss[i].hlpr) {
			stats_free((void *)vss[i].iv);
			vss[i].iv = NULL;
		}
	}
}
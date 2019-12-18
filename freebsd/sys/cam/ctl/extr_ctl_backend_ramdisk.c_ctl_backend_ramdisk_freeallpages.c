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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_RAMDISK ; 
 int PPP ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_freeallpages(uint8_t **p, int indir)
{
	int i;

	if (p == NULL)
		return;
	if (indir == 0) {
		free(p, M_RAMDISK);
		return;
	}
	for (i = 0; i < PPP; i++) {
		if (p[i] == NULL)
			continue;
		ctl_backend_ramdisk_freeallpages((uint8_t **)p[i], indir - 1);
	}
	free(p, M_RAMDISK);
}
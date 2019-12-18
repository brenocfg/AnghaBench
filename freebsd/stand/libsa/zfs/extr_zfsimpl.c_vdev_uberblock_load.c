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
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  uberblock_t ;

/* Variables and functions */
 int VDEV_LABELS ; 
 int VDEV_UBERBLOCK_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_OFFSET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ uberblock_verify (int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_label_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_uberblock_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_uberblock_load(vdev_t *vd, uberblock_t *ub)
{
	uberblock_t *buf;

	buf = malloc(VDEV_UBERBLOCK_SIZE(vd));
	if (buf == NULL)
		return;

	for (int l = 0; l < VDEV_LABELS; l++) {
		for (int n = 0; n < VDEV_UBERBLOCK_COUNT(vd); n++) {
			if (vdev_label_read(vd, l, buf,
			    VDEV_UBERBLOCK_OFFSET(vd, n),
			    VDEV_UBERBLOCK_SIZE(vd)))
				continue;
			if (uberblock_verify(buf) != 0)
				continue;

			if (vdev_uberblock_compare(buf, ub) > 0)
				*ub = *buf;
		}
	}
	free(buf);
}
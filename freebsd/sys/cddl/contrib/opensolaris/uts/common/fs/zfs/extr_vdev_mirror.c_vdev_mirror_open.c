#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vs_aux; } ;
struct TYPE_7__ {int vdev_children; int vdev_open_error; TYPE_1__ vdev_stat; int /*<<< orphan*/  vdev_physical_ashift; int /*<<< orphan*/  vdev_ashift; scalar_t__ vdev_max_asize; scalar_t__ vdev_asize; struct TYPE_7__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDEV_AUX_BAD_LABEL ; 
 int /*<<< orphan*/  VDEV_AUX_CHILDREN_OFFLINE ; 
 int /*<<< orphan*/  VDEV_AUX_NO_REPLICAS ; 
 scalar_t__ vdev_children_are_offline (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_open_children (TYPE_2__*) ; 

__attribute__((used)) static int
vdev_mirror_open(vdev_t *vd, uint64_t *asize, uint64_t *max_asize,
    uint64_t *logical_ashift, uint64_t *physical_ashift)
{
	int numerrors = 0;
	int lasterror = 0;

	if (vd->vdev_children == 0) {
		vd->vdev_stat.vs_aux = VDEV_AUX_BAD_LABEL;
		return (SET_ERROR(EINVAL));
	}

	vdev_open_children(vd);

	for (int c = 0; c < vd->vdev_children; c++) {
		vdev_t *cvd = vd->vdev_child[c];

		if (cvd->vdev_open_error) {
			lasterror = cvd->vdev_open_error;
			numerrors++;
			continue;
		}

		*asize = MIN(*asize - 1, cvd->vdev_asize - 1) + 1;
		*max_asize = MIN(*max_asize - 1, cvd->vdev_max_asize - 1) + 1;
		*logical_ashift = MAX(*logical_ashift, cvd->vdev_ashift);
		*physical_ashift = MAX(*physical_ashift,
		    cvd->vdev_physical_ashift);
	}

	if (numerrors == vd->vdev_children) {
		if (vdev_children_are_offline(vd))
			vd->vdev_stat.vs_aux = VDEV_AUX_CHILDREN_OFFLINE;
		else
			vd->vdev_stat.vs_aux = VDEV_AUX_NO_REPLICAS;
		return (lasterror);
	}

	return (0);
}
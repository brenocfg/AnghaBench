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
struct vpoio_data {int /*<<< orphan*/  vpo_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_SELECT_MICROSEQUENCE ; 
 int /*<<< orphan*/  SELECT_TARGET ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_MS_init_msq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  select_microseq ; 

__attribute__((used)) static char
imm_select(struct vpoio_data *vpo, int initiator, int target)
{
	DECLARE_SELECT_MICROSEQUENCE;
	device_t ppbus = device_get_parent(vpo->vpo_dev);
	int ret;

	/* initialize the select microsequence */
	ppb_MS_init_msq(select_microseq, 1,
			SELECT_TARGET, 1 << initiator | 1 << target);

	ppb_MS_microseq(ppbus, vpo->vpo_dev, select_microseq, &ret);

	return (ret);
}
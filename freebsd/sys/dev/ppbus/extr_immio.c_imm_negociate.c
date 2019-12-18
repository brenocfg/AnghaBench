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
 int /*<<< orphan*/  DECLARE_NEGOCIATE_MICROSEQ ; 
 int /*<<< orphan*/  NEGOCIATED_MODE ; 
 scalar_t__ PPB_IN_NIBBLE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PPB_IN_PS2_MODE (int /*<<< orphan*/ ) ; 
 int VP0_ENEGOCIATE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  negociate_microseq ; 
 int ppb_1284_negociate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_MS_init_msq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
imm_negociate(struct vpoio_data *vpo)
{
	DECLARE_NEGOCIATE_MICROSEQ;
	device_t ppbus = device_get_parent(vpo->vpo_dev);
	int negociate_mode;
	int ret;

	if (PPB_IN_NIBBLE_MODE(ppbus))
		negociate_mode = 0;
	else if (PPB_IN_PS2_MODE(ppbus))
		negociate_mode = 1;
	else
		return (0);

#if 0 /* XXX use standalone code not to depend on ppb_1284 code yet */
	ret = ppb_1284_negociate(ppbus, negociate_mode);

	if (ret)
		return (VP0_ENEGOCIATE);
#endif

	ppb_MS_init_msq(negociate_microseq, 1,
			NEGOCIATED_MODE, negociate_mode);

	ppb_MS_microseq(ppbus, vpo->vpo_dev, negociate_microseq, &ret);

	return (ret);
}
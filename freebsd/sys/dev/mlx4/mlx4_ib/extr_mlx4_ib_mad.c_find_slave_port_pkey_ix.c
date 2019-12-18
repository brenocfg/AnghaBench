#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct TYPE_7__ {size_t*** virt2phys_pkey; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; TYPE_3__ pkeys; TYPE_4__* dev; } ;
struct TYPE_6__ {int* pkey_table_len; } ;
struct TYPE_5__ {size_t* pkey_phys_table_len; } ;
struct TYPE_8__ {TYPE_2__ caps; TYPE_1__ phys_caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int ib_find_cached_pkey (int /*<<< orphan*/ *,size_t,int,int*) ; 
 int ib_get_cached_pkey (int /*<<< orphan*/ *,size_t,size_t,int*) ; 
 int mlx4_master_func_num (TYPE_4__*) ; 

__attribute__((used)) static int find_slave_port_pkey_ix(struct mlx4_ib_dev *dev, int slave,
				   u8 port, u16 pkey, u16 *ix)
{
	int i, ret;
	u8 unassigned_pkey_ix, pkey_ix, partial_ix = 0xFF;
	u16 slot_pkey;

	if (slave == mlx4_master_func_num(dev->dev))
		return ib_find_cached_pkey(&dev->ib_dev, port, pkey, ix);

	unassigned_pkey_ix = dev->dev->phys_caps.pkey_phys_table_len[port] - 1;

	for (i = 0; i < dev->dev->caps.pkey_table_len[port]; i++) {
		if (dev->pkeys.virt2phys_pkey[slave][port - 1][i] == unassigned_pkey_ix)
			continue;

		pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][i];

		ret = ib_get_cached_pkey(&dev->ib_dev, port, pkey_ix, &slot_pkey);
		if (ret)
			continue;
		if ((slot_pkey & 0x7FFF) == (pkey & 0x7FFF)) {
			if (slot_pkey & 0x8000) {
				*ix = (u16) pkey_ix;
				return 0;
			} else {
				/* take first partial pkey index found */
				if (partial_ix == 0xFF)
					partial_ix = pkey_ix;
			}
		}
	}

	if (partial_ix < 0xFF) {
		*ix = (u16) partial_ix;
		return 0;
	}

	return -EINVAL;
}
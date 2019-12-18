#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct octeon_device {size_t octeon_id; int /*<<< orphan*/  chip_id; } ;
struct TYPE_2__ {int conf_type; } ;

/* Variables and functions */
#define  LIO_CFG_TYPE_DEFAULT 128 
 int /*<<< orphan*/  LIO_CN23XX_PF_VID ; 
 int /*<<< orphan*/  default_cn23xx_conf ; 
 TYPE_1__* oct_conf_info ; 

__attribute__((used)) static void *
__lio_retrieve_config_info(struct octeon_device *oct, uint16_t card_type)
{
	void		*ret = NULL;
	uint32_t	oct_id = oct->octeon_id;

	switch (oct_conf_info[oct_id].conf_type) {
	case LIO_CFG_TYPE_DEFAULT:
		if (oct->chip_id == LIO_CN23XX_PF_VID) {
			ret = &default_cn23xx_conf;
		}

		break;
	default:
		break;
	}
	return (ret);
}
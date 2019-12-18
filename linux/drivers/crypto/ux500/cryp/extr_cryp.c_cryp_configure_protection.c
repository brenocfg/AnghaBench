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
typedef  int /*<<< orphan*/  u32 ;
struct cryp_protection_config {int /*<<< orphan*/  privilege_access; scalar_t__ secure_access; } ;
struct cryp_device_data {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_CR_PRLG_MASK ; 
 int /*<<< orphan*/  CRYP_CR_PRLG_POS ; 
 int /*<<< orphan*/  CRYP_CR_SECURE_MASK ; 
 int /*<<< orphan*/  CRYP_PUT_BITS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYP_WRITE_BIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 

int cryp_configure_protection(struct cryp_device_data *device_data,
			      struct cryp_protection_config *p_protect_config)
{
	if (NULL == p_protect_config)
		return -EINVAL;

	CRYP_WRITE_BIT(&device_data->base->cr,
		       (u32) p_protect_config->secure_access,
		       CRYP_CR_SECURE_MASK);
	CRYP_PUT_BITS(&device_data->base->cr,
		      p_protect_config->privilege_access,
		      CRYP_CR_PRLG_POS,
		      CRYP_CR_PRLG_MASK);

	return 0;
}
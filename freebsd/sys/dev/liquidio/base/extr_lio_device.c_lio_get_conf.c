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
struct octeon_device {int dummy; } ;
struct lio_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIO_CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ LIO_CN23XX_PF (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_pf ; 

struct lio_config *
lio_get_conf(struct octeon_device *oct)
{
	struct lio_config	*default_oct_conf = NULL;

	/*
	 * check the OCTEON Device model & return the corresponding octeon
	 * configuration
	 */
	if (LIO_CN23XX_PF(oct)) {
		default_oct_conf = (struct lio_config *)(
					       LIO_CHIP_CONF(oct, cn23xx_pf));
	}

	return (default_oct_conf);
}
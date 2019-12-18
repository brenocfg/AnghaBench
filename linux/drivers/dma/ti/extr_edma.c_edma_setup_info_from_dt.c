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
struct edma_soc_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct edma_soc_info* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct edma_soc_info *edma_setup_info_from_dt(struct device *dev,
						     bool legacy_mode)
{
	return ERR_PTR(-EINVAL);
}
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
struct scpi_dvfs_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scpi_dvfs_info* ERR_PTR (int) ; 
 int scpi_dev_domain_id (struct device*) ; 
 struct scpi_dvfs_info* scpi_dvfs_get_info (int) ; 

__attribute__((used)) static struct scpi_dvfs_info *scpi_dvfs_info(struct device *dev)
{
	int domain = scpi_dev_domain_id(dev);

	if (domain < 0)
		return ERR_PTR(domain);

	return scpi_dvfs_get_info(domain);
}
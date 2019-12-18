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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOV_CONFIG_NAME ; 
 int /*<<< orphan*/  PF_CONFIG_NAME ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

uint16_t
pci_iov_config_get_num_vfs(const nvlist_t *config)
{
	const nvlist_t *pf, *iov;

	pf = nvlist_get_nvlist(config, PF_CONFIG_NAME);
	iov = nvlist_get_nvlist(pf, IOV_CONFIG_NAME);
	return (nvlist_get_number(iov, "num_vfs"));
}
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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  OPAL_GET_DEVICE_TREE ; 
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  opal_check_token (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_get_device_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pnv_pci_get_device_tree(uint32_t phandle, void *buf, uint64_t len)
{
	int64_t rc;

	if (!opal_check_token(OPAL_GET_DEVICE_TREE))
		return -ENXIO;

	rc = opal_get_device_tree(phandle, (uint64_t)buf, len);
	if (rc < OPAL_SUCCESS)
		return -EIO;

	return rc;
}
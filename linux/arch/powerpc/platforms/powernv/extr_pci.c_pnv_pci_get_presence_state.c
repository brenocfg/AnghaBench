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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  OPAL_PCI_GET_PRESENCE_STATE ; 
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  opal_check_token (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_pci_get_presence_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pnv_pci_get_presence_state(uint64_t id, uint8_t *state)
{
	int64_t rc;

	if (!opal_check_token(OPAL_PCI_GET_PRESENCE_STATE))
		return -ENXIO;

	rc = opal_pci_get_presence_state(id, (uint64_t)state);
	if (rc != OPAL_SUCCESS)
		return -EIO;

	return 0;
}
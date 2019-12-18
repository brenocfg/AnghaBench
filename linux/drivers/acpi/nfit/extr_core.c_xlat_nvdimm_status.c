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
typedef  int u32 ;
struct nvdimm {int dummy; } ;
struct nfit_mem {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ACPI_LABELS_LOCKED ; 
 int EACCES ; 
 int EIO ; 
#define  ND_CMD_GET_CONFIG_DATA 130 
#define  ND_CMD_GET_CONFIG_SIZE 129 
#define  ND_CMD_SET_CONFIG_DATA 128 
 int ND_CONFIG_LOCKED ; 
 int /*<<< orphan*/  NFIT_MEM_LSR ; 
 int /*<<< orphan*/  NFIT_MEM_LSW ; 
 struct nfit_mem* nvdimm_provider_data (struct nvdimm*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xlat_nvdimm_status(struct nvdimm *nvdimm, void *buf, unsigned int cmd,
		u32 status)
{
	struct nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	switch (cmd) {
	case ND_CMD_GET_CONFIG_SIZE:
		/*
		 * In the _LSI, _LSR, _LSW case the locked status is
		 * communicated via the read/write commands
		 */
		if (test_bit(NFIT_MEM_LSR, &nfit_mem->flags))
			break;

		if (status >> 16 & ND_CONFIG_LOCKED)
			return -EACCES;
		break;
	case ND_CMD_GET_CONFIG_DATA:
		if (test_bit(NFIT_MEM_LSR, &nfit_mem->flags)
				&& status == ACPI_LABELS_LOCKED)
			return -EACCES;
		break;
	case ND_CMD_SET_CONFIG_DATA:
		if (test_bit(NFIT_MEM_LSW, &nfit_mem->flags)
				&& status == ACPI_LABELS_LOCKED)
			return -EACCES;
		break;
	default:
		break;
	}

	/* all other non-zero status results in an error */
	if (status)
		return -EIO;
	return 0;
}
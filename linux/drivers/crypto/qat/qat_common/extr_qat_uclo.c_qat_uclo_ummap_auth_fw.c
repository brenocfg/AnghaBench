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
struct icp_qat_fw_loader_handle {int dummy; } ;
struct icp_qat_fw_auth_desc {int dummy; } ;
struct icp_qat_auth_chunk {int /*<<< orphan*/  chunk_size; int /*<<< orphan*/  chunk_bus_addr; } ;
struct icp_firml_dram_desc {int /*<<< orphan*/  dram_size; int /*<<< orphan*/  dram_bus_addr; struct icp_qat_fw_auth_desc* dram_base_addr_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  qat_uclo_simg_free (struct icp_qat_fw_loader_handle*,struct icp_firml_dram_desc*) ; 

__attribute__((used)) static void qat_uclo_ummap_auth_fw(struct icp_qat_fw_loader_handle *handle,
				   struct icp_qat_fw_auth_desc **desc)
{
	struct icp_firml_dram_desc dram_desc;

	dram_desc.dram_base_addr_v = *desc;
	dram_desc.dram_bus_addr = ((struct icp_qat_auth_chunk *)
				   (*desc))->chunk_bus_addr;
	dram_desc.dram_size = ((struct icp_qat_auth_chunk *)
			       (*desc))->chunk_size;
	qat_uclo_simg_free(handle, &dram_desc);
}
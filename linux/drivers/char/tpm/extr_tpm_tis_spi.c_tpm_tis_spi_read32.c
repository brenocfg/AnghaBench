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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tpm_tis_data {TYPE_1__* phy_ops; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int (* read_bytes ) (struct tpm_tis_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct tpm_tis_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm_tis_spi_read32(struct tpm_tis_data *data, u32 addr, u32 *result)
{
	__le32 result_le;
	int rc;

	rc = data->phy_ops->read_bytes(data, addr, sizeof(u32),
				       (u8 *)&result_le);
	if (!rc)
		*result = le32_to_cpu(result_le);

	return rc;
}
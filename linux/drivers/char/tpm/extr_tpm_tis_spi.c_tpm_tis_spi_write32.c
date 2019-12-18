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
struct TYPE_2__ {int (* write_bytes ) (struct tpm_tis_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int stub1 (struct tpm_tis_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm_tis_spi_write32(struct tpm_tis_data *data, u32 addr, u32 value)
{
	__le32 value_le;
	int rc;

	value_le = cpu_to_le32(value);
	rc = data->phy_ops->write_bytes(data, addr, sizeof(u32),
					(u8 *)&value_le);

	return rc;
}
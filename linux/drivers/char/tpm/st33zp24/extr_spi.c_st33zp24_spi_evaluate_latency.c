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
typedef  int /*<<< orphan*/  u8 ;
struct st33zp24_spi_phy {int latency; } ;

/* Variables and functions */
 int ENODEV ; 
 int MAX_SPI_LATENCY ; 
 int /*<<< orphan*/  TPM_INTF_CAPABILITY ; 
 int st33zp24_spi_read8_reg (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int st33zp24_spi_evaluate_latency(void *phy_id)
{
	struct st33zp24_spi_phy *phy = phy_id;
	int latency = 1, status = 0;
	u8 data = 0;

	while (!status && latency < MAX_SPI_LATENCY) {
		phy->latency = latency;
		status = st33zp24_spi_read8_reg(phy_id, TPM_INTF_CAPABILITY,
						&data, 1);
		latency++;
	}
	if (status < 0)
		return status;
	if (latency == MAX_SPI_LATENCY)
		return -ENODEV;

	return latency - 1;
}
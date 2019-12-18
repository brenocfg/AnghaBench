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
struct iic_dp_aux_data {int /*<<< orphan*/  running; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MODE_I2C_READ ; 
 struct iic_dp_aux_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int iic_dp_aux_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iic_dp_aux_get_byte(device_t idev, u8 *byte_ret)
{
	struct iic_dp_aux_data *aux_data;
	int ret;

	aux_data = device_get_softc(idev);

	if (!aux_data->running)
		return (-EIO);

	ret = iic_dp_aux_transaction(idev, MODE_I2C_READ, 0, byte_ret);
	return (ret);
}
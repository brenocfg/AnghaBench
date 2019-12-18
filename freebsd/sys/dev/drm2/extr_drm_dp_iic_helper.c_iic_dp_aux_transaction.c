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
struct iic_dp_aux_data {int (* aux_ch ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iic_dp_aux_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iic_dp_aux_transaction(device_t idev, int mode, uint8_t write_byte,
    uint8_t *read_byte)
{
	struct iic_dp_aux_data *aux_data;
	int ret;

	aux_data = device_get_softc(idev);
	ret = (*aux_data->aux_ch)(idev, mode, write_byte, read_byte);
	if (ret < 0)
		return (ret);
	return (0);
}
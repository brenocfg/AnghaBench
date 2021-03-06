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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct iic_msg {int member_1; int member_2; char* member_3; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int IIC_M_WR ; 
 int TRANSFER_MSGS (int /*<<< orphan*/ ,struct iic_msg*) ; 
 int iic2smb_error (int) ; 
 int nitems (int*) ; 

__attribute__((used)) static int
iicsmb_readw(device_t dev, u_char slave, char cmd, short *word)
{
	uint8_t buf[2];
	struct iic_msg msgs[] = {
	     { slave, IIC_M_WR | IIC_M_NOSTOP, 1, &cmd },
	     { slave, IIC_M_RD, nitems(buf), buf },
	};
	int error;

	error = TRANSFER_MSGS(dev, msgs);
	if (error == 0)
		*word = ((uint16_t)buf[1] << 8) | buf[0];
	return (iic2smb_error(error));
}
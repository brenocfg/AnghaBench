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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct iic_msg {char* member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int TRANSFER_MSGS (int /*<<< orphan*/ ,struct iic_msg*) ; 
 int iic2smb_error (int) ; 
 int /*<<< orphan*/  nitems (char*) ; 

__attribute__((used)) static int
iicsmb_writew(device_t dev, u_char slave, char cmd, short word)
{
	uint8_t bytes[] = { cmd, word & 0xff, word >> 8 };
	struct iic_msg msgs[] = {
	     { slave, IIC_M_WR, nitems(bytes), bytes },
	};
	int error;

	error = TRANSFER_MSGS(dev, msgs);
	return (iic2smb_error(error));
}
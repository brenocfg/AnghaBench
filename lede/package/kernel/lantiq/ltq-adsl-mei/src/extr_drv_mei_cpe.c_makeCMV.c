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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int H2D_CMV_WRITE ; 
 int MSG_LENGTH ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void
makeCMV (u8 opcode, u8 group, u16 address, u16 index, int size, u16 * data, u16 *CMVMSG)
{
        memset (CMVMSG, 0, MSG_LENGTH * 2);
        CMVMSG[0] = (opcode << 4) + (size & 0xf);
        CMVMSG[1] = (((index == 0) ? 0 : 1) << 7) + (group & 0x7f);
        CMVMSG[2] = address;
        CMVMSG[3] = index;
        if (opcode == H2D_CMV_WRITE)
                memcpy (CMVMSG + 4, data, size * 2);
        return;
}
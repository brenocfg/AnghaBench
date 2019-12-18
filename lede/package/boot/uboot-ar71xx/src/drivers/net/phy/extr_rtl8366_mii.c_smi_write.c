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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  smi_start () ; 
 int /*<<< orphan*/  smi_stop () ; 
 scalar_t__ smi_waitAck () ; 
 int /*<<< orphan*/  smi_writeBits (int,int) ; 

__attribute__((used)) static int smi_write(uint32_t reg, uint32_t data)
{
    /* send start condition */
    smi_start();
    /* send CTRL1 code: 0b1010*/
    smi_writeBits(0x0a, 4);
    /* send CTRL2 code: 0b100 */
    smi_writeBits(0x04, 3);
    /* send WRITE command */
    smi_writeBits(0x00, 1);

    /* wait for ACK */
    if (smi_waitAck())
        return -1;

    /* send address low */
    smi_writeBits(reg & 0xFF, 8);
    /* wait for ACK */
    if (smi_waitAck())
        return -1;
    /* send address high */
    smi_writeBits((reg & 0xFF00) >> 8, 8);
    /* wait for ACK */
    if (smi_waitAck())
        return -1;

    /* send data low */
    smi_writeBits(data & 0xFF, 8);
    /* wait for ACK */
    if (smi_waitAck())
        return -1;
    /* send data high */
    smi_writeBits((data & 0xFF00) >> 8, 8);
    /* wait for ACK */
    if (smi_waitAck())
        return -1;

    /* send stop condition */
    smi_stop();

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bktr_ptr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dpl_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  msp_dpl_write (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 

void dpl_autodetect( bktr_ptr_t bktr ) {

    /* The following are empiric values tried from the DPL35xx data sheet */
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x000c,0x0320);	/* quasi peak detector source dolby
								lr 0x03xx; quasi peak detector matrix
								stereo 0xXX20 */
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x0040,0x0060);	/* Surround decoder mode;
								ADAPTIVE/3D-PANORAMA, that means two
								speakers and no center speaker, all
								channels L/R/C/S mixed to L and R */
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x0041,0x0620);	/* surround source matrix;I2S2/STEREO*/
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x0042,0x1F00);	/* surround delay 31ms max */
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x0043,0x0000);	/* automatic surround input balance */
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x0044,0x4000);	/* surround spatial effect 50%
								recommended*/
    msp_dpl_write(bktr, bktr->dpl_addr, 0x12, 0x0045,0x5400);	/* surround panorama effect 66%
								recommended with PANORAMA mode
								in 0x0040 set to panorama */
}
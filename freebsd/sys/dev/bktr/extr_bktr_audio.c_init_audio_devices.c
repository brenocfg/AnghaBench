#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* bktr_ptr_t ;
struct TYPE_6__ {scalar_t__ dpl3518a; scalar_t__ msp3400c; scalar_t__ dbx; } ;
struct TYPE_7__ {int /*<<< orphan*/  dpl_addr; TYPE_1__ card; int /*<<< orphan*/  msp_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_BTSC (TYPE_2__*) ; 
 int /*<<< orphan*/  msp_dpl_reset (TYPE_2__*,int /*<<< orphan*/ ) ; 

void init_audio_devices( bktr_ptr_t bktr ) {

        /* enable stereo if appropriate on TDA audio chip */
        if ( bktr->card.dbx )
                init_BTSC( bktr );
 
        /* reset the MSP34xx stereo audio chip */
        if ( bktr->card.msp3400c )
                msp_dpl_reset( bktr, bktr->msp_addr );

        /* reset the DPL35xx dolby audio chip */
        if ( bktr->card.dpl3518a )
                msp_dpl_reset( bktr, bktr->dpl_addr );

}
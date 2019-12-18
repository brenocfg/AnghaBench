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
struct TYPE_4__ {int audio_mux_select; scalar_t__ audio_mute_state; } ;

/* Variables and functions */
#define  BCTV2_AUDIO_BOTH 130 
#define  BCTV2_AUDIO_MAIN 129 
#define  BCTV2_AUDIO_SUB 128 
 int /*<<< orphan*/  BCTV2_GPIO_REG0 ; 
 int /*<<< orphan*/  BCTV2_GPIO_REG1 ; 
 int BCTV2_GR0_AUDIO_BOTH ; 
 int BCTV2_GR0_AUDIO_MAIN ; 
 int BCTV2_GR0_AUDIO_MUTE ; 
 int BCTV2_GR0_AUDIO_SUB ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bctv2_gpio_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
set_bctv2_audio( bktr_ptr_t bktr )
{
        int data;

        switch (bktr->audio_mux_select) {
        case 1:         /* external */
        case 2:         /* internal */
                bctv2_gpio_write(bktr, BCTV2_GPIO_REG1, 0);
                break;
        default:        /* tuner */
                bctv2_gpio_write(bktr, BCTV2_GPIO_REG1, 1);
                break;
        }
/*      switch (bktr->audio_sap_select) { */
        switch (BCTV2_AUDIO_BOTH) {
        case BCTV2_AUDIO_SUB:
                data = BCTV2_GR0_AUDIO_SUB;
                break;
        case BCTV2_AUDIO_BOTH:
                data = BCTV2_GR0_AUDIO_BOTH;
                break;
        case BCTV2_AUDIO_MAIN:
        default:
                data = BCTV2_GR0_AUDIO_MAIN;
                break;
        }
        if (bktr->audio_mute_state == TRUE)
                data |= BCTV2_GR0_AUDIO_MUTE;

        bctv2_gpio_write(bktr, BCTV2_GPIO_REG0, data);

        return;
}
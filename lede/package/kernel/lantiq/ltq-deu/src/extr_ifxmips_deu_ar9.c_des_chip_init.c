#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int SM; int ARS; } ;
struct des_t {TYPE_1__ controlr; } ;

/* Variables and functions */
 scalar_t__ DES_3DES_START ; 

void des_chip_init (void)
{
    volatile struct des_t *des = (struct des_t *) DES_3DES_START;

    // start crypto engine with write to ILR
    des->controlr.SM = 1;
    asm("sync");
    des->controlr.ARS = 1;

}
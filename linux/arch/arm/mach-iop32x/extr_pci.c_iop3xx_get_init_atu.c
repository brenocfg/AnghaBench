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

/* Variables and functions */
 scalar_t__ IOP3XX_INIT_ATU_DEFAULT ; 
 int IOP3XX_INIT_ATU_DISABLE ; 
 scalar_t__ init_atu ; 

int iop3xx_get_init_atu(void) {
	/* check if default has been overridden */
	if (init_atu != IOP3XX_INIT_ATU_DEFAULT)
		return init_atu;
	else
		return IOP3XX_INIT_ATU_DISABLE;
}
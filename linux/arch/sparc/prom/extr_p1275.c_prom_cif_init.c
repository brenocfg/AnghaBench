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
struct TYPE_2__ {void (* prom_cif_handler ) (long*) ;} ;

/* Variables and functions */
 TYPE_1__ p1275buf ; 

void prom_cif_init(void *cif_handler, void *cif_stack)
{
	p1275buf.prom_cif_handler = (void (*)(long *))cif_handler;
}
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
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 long PCI66 ; 
 int USE_DPLL ; 

__attribute__((used)) static int hpt3x2n_use_dpll(struct ata_port *ap, int writing)
{
	long flags = (long)ap->host->private_data;

	/* See if we should use the DPLL */
	if (writing)
		return USE_DPLL;	/* Needed for write */
	if (flags & PCI66)
		return USE_DPLL;	/* Needed at 66Mhz */
	return 0;
}
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
struct ahc_softc {int bugs; } ;

/* Variables and functions */
 int AHC_PCI_2_1_RETRY_BUG ; 

__attribute__((used)) static int
ahc_patch18_func(struct ahc_softc *ahc)
{
	return ((ahc->bugs & AHC_PCI_2_1_RETRY_BUG) != 0);
}
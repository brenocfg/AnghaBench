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
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 void BHND_EROM_FINI (int /*<<< orphan*/ *) ; 

void
bhnd_erom_fini_static(bhnd_erom_t *erom)
{
	return (BHND_EROM_FINI(erom));
}
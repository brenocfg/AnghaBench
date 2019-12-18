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
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_EROM_FINI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bhnd_erom_free(bhnd_erom_t *erom)
{
	BHND_EROM_FINI(erom);
	kobj_delete((kobj_t)erom, M_BHND);
}
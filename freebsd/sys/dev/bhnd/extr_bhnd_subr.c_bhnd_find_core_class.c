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
typedef  int /*<<< orphan*/  uint16_t ;
struct bhnd_core_desc {int /*<<< orphan*/  class; } ;
typedef  int /*<<< orphan*/  bhnd_devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_DEVCLASS_OTHER ; 
 struct bhnd_core_desc* bhnd_find_core_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bhnd_devclass_t
bhnd_find_core_class(uint16_t vendor, uint16_t device)
{
	const struct bhnd_core_desc *desc;
	
	if ((desc = bhnd_find_core_desc(vendor, device)) == NULL)
		return (BHND_DEVCLASS_OTHER);

	return desc->class;
}
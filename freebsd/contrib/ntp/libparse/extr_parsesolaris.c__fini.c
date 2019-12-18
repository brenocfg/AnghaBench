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
 scalar_t__ DDI_SUCCESS ; 
 int EBUSY ; 
 scalar_t__ mod_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modlinkage ; 

int
_fini(
      void
      )
{
	if (mod_remove(&modlinkage) != DDI_SUCCESS)
	{
		return EBUSY;
	}
	else
	    return DDI_SUCCESS;
}
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
 unsigned int TURRIS_MOX_MODULE_FIRST ; 
 unsigned int TURRIS_MOX_MODULE_LAST ; 

__attribute__((used)) static inline bool mox_module_known(unsigned int id)
{
	return id >= TURRIS_MOX_MODULE_FIRST && id <= TURRIS_MOX_MODULE_LAST;
}
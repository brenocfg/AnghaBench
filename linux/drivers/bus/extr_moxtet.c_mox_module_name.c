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
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 scalar_t__ mox_module_known (unsigned int) ; 
 TYPE_1__* mox_module_table ; 

__attribute__((used)) static inline const char *mox_module_name(unsigned int id)
{
	if (mox_module_known(id))
		return mox_module_table[id].name;
	else
		return "unknown";
}
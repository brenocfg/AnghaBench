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
typedef  enum MAD_FIELDS { ____Placeholder_MAD_FIELDS } MAD_FIELDS ;

/* Variables and functions */
 int sup_total ; 
 int* suppressed_fields ; 

__attribute__((used)) static int suppress(enum MAD_FIELDS field)
{
	int i = 0;
	for (i = 0; i < sup_total; i++)
		if (field == suppressed_fields[i])
			return 1;
	return 0;
}
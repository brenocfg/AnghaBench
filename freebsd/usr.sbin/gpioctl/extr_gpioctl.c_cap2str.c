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
typedef  scalar_t__ uint32_t ;
struct flag_desc {char const* name; scalar_t__ flag; } ;

/* Variables and functions */
 struct flag_desc* gpio_flags ; 

__attribute__((used)) static const char *
cap2str(uint32_t cap)
{
	struct flag_desc * pdesc = gpio_flags;
	while (pdesc->name) {
		if (pdesc->flag == cap)
			return pdesc->name;
		pdesc++;
	}

	return "UNKNOWN";
}
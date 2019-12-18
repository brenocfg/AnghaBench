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
struct flag_desc {int flag; scalar_t__ name; } ;

/* Variables and functions */
 struct flag_desc* gpio_flags ; 
 scalar_t__ strcasecmp (char const*,scalar_t__) ; 

int
str2cap(const char *str)
{
	struct flag_desc * pdesc = gpio_flags;
	while (pdesc->name) {
		if (strcasecmp(str, pdesc->name) == 0)
			return pdesc->flag;
		pdesc++;
	}

	return (-1);
}
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
struct res_sym {scalar_t__ name; int number; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,scalar_t__) ; 

int
sym_ston(const struct res_sym *syms, const char *name, int *success) {
	for ((void)NULL; syms->name != 0; syms++) {
		if (strcasecmp (name, syms->name) == 0) {
			if (success)
				*success = 1;
			return (syms->number);
		}
	}
	if (success)
		*success = 0;
	return (syms->number);		/*%< The default value. */
}
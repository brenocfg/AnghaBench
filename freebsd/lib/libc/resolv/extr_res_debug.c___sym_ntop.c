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
struct res_sym {scalar_t__ name; int number; char const* humanname; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* sym_ntop_unname ; 

const char *
sym_ntop(const struct res_sym *syms, int number, int *success) {
	char *unname = sym_ntop_unname;

	for ((void)NULL; syms->name != 0; syms++) {
		if (number == syms->number) {
			if (success)
				*success = 1;
			return (syms->humanname);
		}
	}
	sprintf(unname, "%d", number);		/*%< XXX nonreentrant */
	if (success)
		*success = 0;
	return (unname);
}
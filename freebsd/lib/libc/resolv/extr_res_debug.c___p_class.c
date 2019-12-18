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
 int /*<<< orphan*/  __p_class_syms ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* sym_ntos (int /*<<< orphan*/ ,int,int*) ; 

const char *
p_class(int class) {
	int success;
	const char *result;
	static char classbuf[20];

	result = sym_ntos(__p_class_syms, class, &success);
	if (success)
		return (result);
	if (class < 0 || class > 0xffff)
		return ("BADCLASS");
	sprintf(classbuf, "CLASS%d", class);
	return (classbuf);
}
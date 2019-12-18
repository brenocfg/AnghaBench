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
typedef  enum uni_verb { ____Placeholder_uni_verb } uni_verb ;

/* Variables and functions */
 int UNI_MAXFACILITY ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char const** verb_names ; 

const char *
uni_facname(enum uni_verb fac)
{
	static char buf[40];

	if (fac >= UNI_MAXFACILITY) {
		sprintf(buf, "FAC%u", fac);
		return (buf);
	}
	return (verb_names[fac]);
}
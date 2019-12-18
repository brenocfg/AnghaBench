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
typedef  int u_int32_t ;
struct compression_types {char const* name; int comp_number; } ;

/* Variables and functions */
 int MT_COMP_DISABLED ; 
 int MT_COMP_UNSUPP ; 
 struct compression_types* comp_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char *
comptostring(u_int32_t comp)
{
	static char buf[20];
	const struct compression_types *ct;

	if (comp == MT_COMP_DISABLED)
		return "disabled";
	else if (comp == MT_COMP_UNSUPP)
		return "unsupported";

	for (ct = comp_types; ct->name; ct++)
		if (ct->comp_number == comp)
			break;

	if (ct->comp_number == 0xf0f0f0f0) {
		sprintf(buf, "0x%x", comp);
		return(buf);
	} else
		return(ct->name);
}
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
typedef  int restrict_op ;

/* Variables and functions */
#define  RESTRICT_FLAGS 131 
#define  RESTRICT_REMOVE 130 
#define  RESTRICT_REMOVEIF 129 
#define  RESTRICT_UNFLAG 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

char *
roptoa(restrict_op op) {
	static char sb[30];

	switch(op) {
	    case RESTRICT_FLAGS:	return "RESTRICT_FLAGS";
	    case RESTRICT_UNFLAG:	return "RESTRICT_UNFLAGS";
	    case RESTRICT_REMOVE:	return "RESTRICT_REMOVE";
	    case RESTRICT_REMOVEIF:	return "RESTRICT_REMOVEIF";
	    default:
		snprintf(sb, sizeof sb, "**RESTRICT_#%d**", op);
		return sb;
	}
}
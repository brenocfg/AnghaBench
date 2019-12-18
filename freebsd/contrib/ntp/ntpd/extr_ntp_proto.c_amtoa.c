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
#define  AM_BCST 136 
#define  AM_ERR 135 
#define  AM_FXMIT 134 
#define  AM_MANYCAST 133 
#define  AM_NEWBCL 132 
#define  AM_NEWPASS 131 
#define  AM_NOMATCH 130 
#define  AM_POSSBCL 129 
#define  AM_PROCPKT 128 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

const char *
amtoa(
	int am
	)
{
	char *bp;

	switch(am) {
	    case AM_ERR:	return "AM_ERR";
	    case AM_NOMATCH:	return "AM_NOMATCH";
	    case AM_PROCPKT:	return "AM_PROCPKT";
	    case AM_BCST:	return "AM_BCST";
	    case AM_FXMIT:	return "AM_FXMIT";
	    case AM_MANYCAST:	return "AM_MANYCAST";
	    case AM_NEWPASS:	return "AM_NEWPASS";
	    case AM_NEWBCL:	return "AM_NEWBCL";
	    case AM_POSSBCL:	return "AM_POSSBCL";
	    default:
		LIB_GETBUF(bp);
		snprintf(bp, LIB_BUFLENGTH, "AM_#%d", am);
		return bp;
	}
}
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
typedef  int u_char ;
typedef  int /*<<< orphan*/  rbuf ;

/* Variables and functions */
#define  SES_OBJSTAT_CRIT 136 
#define  SES_OBJSTAT_NOACCESS 135 
#define  SES_OBJSTAT_NONCRIT 134 
#define  SES_OBJSTAT_NOTAVAIL 133 
#define  SES_OBJSTAT_NOTINSTALLED 132 
#define  SES_OBJSTAT_OK 131 
#define  SES_OBJSTAT_UNKNOWN 130 
#define  SES_OBJSTAT_UNRECOV 129 
#define  SES_OBJSTAT_UNSUPPORTED 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
scode2ascii(u_char code)
{
	static char rbuf[32];
	switch (code & 0xf) {
	case SES_OBJSTAT_UNSUPPORTED:
		return ("Unsupported");
	case SES_OBJSTAT_OK:
		return ("OK");
	case SES_OBJSTAT_CRIT:
		return ("Critical");
	case SES_OBJSTAT_NONCRIT:
		return ("Noncritical");
	case SES_OBJSTAT_UNRECOV:
		return ("Unrecoverable");
	case SES_OBJSTAT_NOTINSTALLED:
		return ("Not Installed");
	case SES_OBJSTAT_UNKNOWN:
		return ("Unknown");
	case SES_OBJSTAT_NOTAVAIL:
		return ("Not Available");
	case SES_OBJSTAT_NOACCESS:
		return ("No Access Allowed");
	default:
		snprintf(rbuf, sizeof(rbuf), "<Status 0x%x>", code & 0xf);
		return (rbuf);
	}
}
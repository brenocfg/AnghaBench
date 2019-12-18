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
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static char *
scode2ascii(u_char code)
{
	static char rbuf[32];
	switch (code & 0xf) {
	case SES_OBJSTAT_UNSUPPORTED:
		sprintf(rbuf, "Unsupported");
		break;
	case SES_OBJSTAT_OK:
		sprintf(rbuf, "OK");
		break;
	case SES_OBJSTAT_CRIT:
		sprintf(rbuf, "Critical");
		break;
	case SES_OBJSTAT_NONCRIT:
		sprintf(rbuf, "Noncritical");
		break;
	case SES_OBJSTAT_UNRECOV:
		sprintf(rbuf, "Unrecoverable");
		break;
	case SES_OBJSTAT_NOTINSTALLED:
		sprintf(rbuf, "Not Installed");
		break;
	case SES_OBJSTAT_UNKNOWN:
		sprintf(rbuf, "Unknown");
		break;
	case SES_OBJSTAT_NOTAVAIL:
		sprintf(rbuf, "Not Available");
		break;
	case SES_OBJSTAT_NOACCESS:
		sprintf(rbuf, "No Access Allowed");
		break;
	default:
		sprintf(rbuf, "<Status 0x%x>", code & 0xf);
		break;
	}
	return (rbuf);
}
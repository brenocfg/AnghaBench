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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BYPERLINE ; 
 int /*<<< orphan*/  NGLOGX (char*,char*) ; 
 scalar_t__ isprint (int const) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

void
_NgDebugBytes(const u_char *ptr, int len)
{
	char    buf[100];
	int     k, count;

#define BYPERLINE	16

	for (count = 0; count < len; ptr += BYPERLINE, count += BYPERLINE) {

		/* Do hex */
		snprintf(buf, sizeof(buf), "%04x:  ", count);
		for (k = 0; k < BYPERLINE; k++, count++)
			if (count < len)
				snprintf(buf + strlen(buf),
				    sizeof(buf) - strlen(buf), "%02x ", ptr[k]);
			else
				snprintf(buf + strlen(buf),
				    sizeof(buf) - strlen(buf), "   ");
		snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "  ");
		count -= BYPERLINE;

		/* Do ASCII */
		for (k = 0; k < BYPERLINE; k++, count++)
			if (count < len)
				snprintf(buf + strlen(buf),
				    sizeof(buf) - strlen(buf),
				    "%c", isprint(ptr[k]) ? ptr[k] : '.');
			else
				snprintf(buf + strlen(buf),
				    sizeof(buf) - strlen(buf), "  ");
		count -= BYPERLINE;

		/* Print it */
		NGLOGX("%s", buf);
	}
}
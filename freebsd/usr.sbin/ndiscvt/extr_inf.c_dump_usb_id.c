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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  ofp ; 
 char* strcasestr (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void
dump_usb_id(const char *s)
{
	char *p;
	char vidstr[7], pidstr[7];

	p = strcasestr(s, "VID_");
	if (p == NULL)
		return;
	p += 4;
	strcpy(vidstr, "0x");
	strncat(vidstr, p, 4);
	p = strcasestr(s, "PID_");
	if (p == NULL)
		return;
	p += 4;
	strcpy(pidstr, "0x");
	strncat(pidstr, p, 4);
	if (p == NULL)
		return;

	fprintf(ofp, "\t\\\n\t{ %s, %s, ", vidstr, pidstr);
}
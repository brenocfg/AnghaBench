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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ofp ; 
 char* strcasestr (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void
dump_pci_id(const char *s)
{
	char *p;
	char vidstr[7], didstr[7], subsysstr[14];

	p = strcasestr(s, "VEN_");
	if (p == NULL)
		return;
	p += 4;
	strcpy(vidstr, "0x");
	strncat(vidstr, p, 4);
	p = strcasestr(s, "DEV_");
	if (p == NULL)
		return;
	p += 4;
	strcpy(didstr, "0x");
	strncat(didstr, p, 4);
	if (p == NULL)
		return;
	p = strcasestr(s, "SUBSYS_");
	if (p == NULL)
		strcpy(subsysstr, "0x00000000");
	else {
		p += 7;
		strcpy(subsysstr, "0x");
		strncat(subsysstr, p, 8);
	}

	fprintf(ofp, "\t\\\n\t{ %s, %s, %s, ", vidstr, didstr, subsysstr);
	return;
}
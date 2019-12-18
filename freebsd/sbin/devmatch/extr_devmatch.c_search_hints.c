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
#define  MDT_MODULE 130 
#define  MDT_PNP_INFO 129 
#define  MDT_VERSION 128 
 int /*<<< orphan*/  all_flag ; 
 int /*<<< orphan*/  dump_flag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getint (void**) ; 
 int /*<<< orphan*/  getstr (void**,char*) ; 
 void* hints ; 
 void* hints_end ; 
 int pnpval_as_int (char*,char const*) ; 
 char* pnpval_as_str (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ unbound_flag ; 
 scalar_t__ verbose_flag ; 

__attribute__((used)) static void
search_hints(const char *bus, const char *dev, const char *pnpinfo)
{
	char val1[256], val2[256];
	int ival, len, ents, i, notme, mask, bit, v, found;
	void *ptr, *walker;
	char *lastmod = NULL, *cp, *s;

	walker = hints;
	getint(&walker);
	found = 0;
	if (verbose_flag)
		printf("Searching bus %s dev %s for pnpinfo %s\n",
		    bus, dev, pnpinfo);
	while (walker < hints_end) {
		len = getint(&walker);
		ival = getint(&walker);
		ptr = walker;
		switch (ival) {
		case MDT_VERSION:
			getstr(&ptr, val1);
			ival = getint(&ptr);
			getstr(&ptr, val2);
			if (dump_flag || verbose_flag)
				printf("Version: if %s.%d kmod %s\n", val1, ival, val2);
			break;
		case MDT_MODULE:
			getstr(&ptr, val1);
			getstr(&ptr, val2);
			if (lastmod)
				free(lastmod);
			lastmod = strdup(val2);
			if (dump_flag || verbose_flag)
				printf("Module %s in %s\n", val1, val2);
			break;
		case MDT_PNP_INFO:
			if (!dump_flag && !unbound_flag && lastmod && strcmp(lastmod, "kernel") == 0)
				break;
			getstr(&ptr, val1);
			getstr(&ptr, val2);
			ents = getint(&ptr);
			if (dump_flag || verbose_flag)
				printf("PNP info for bus %s format %s %d entries (%s)\n",
				    val1, val2, ents, lastmod);
			if (strcmp(val1, "usb") == 0) {
				if (verbose_flag)
					printf("Treating usb as uhub -- bug in source table still?\n");
				strcpy(val1, "uhub");
			}
			if (bus && strcmp(val1, bus) != 0) {
				if (verbose_flag)
					printf("Skipped because table for bus %s, looking for %s\n",
					    val1, bus);
				break;
			}
			for (i = 0; i < ents; i++) {
				if (verbose_flag)
					printf("---------- Entry %d ----------\n", i);
				if (dump_flag)
					printf("   ");
				cp = val2;
				notme = 0;
				mask = -1;
				bit = -1;
				do {
					switch (*cp) {
						/* All integer fields */
					case 'I':
					case 'J':
					case 'G':
					case 'L':
					case 'M':
						ival = getint(&ptr);
						if (dump_flag) {
							printf("%#x:", ival);
							break;
						}
						if (bit >= 0 && ((1 << bit) & mask) == 0)
							break;
						v = pnpval_as_int(cp + 2, pnpinfo);
						if (verbose_flag)
							printf("Matching %s (%c) table=%#x tomatch=%#x\n",
							    cp + 2, *cp, v, ival);
						switch (*cp) {
						case 'J':
							if (ival == -1)
								break;
							/*FALLTHROUGH*/
						case 'I':
							if (v != ival)
								notme++;
							break;
						case 'G':
							if (v < ival)
								notme++;
							break;
						case 'L':
							if (v > ival)
								notme++;
							break;
						case 'M':
							mask = ival;
							break;
						}
						break;
						/* String fields */
					case 'D':
					case 'Z':
						getstr(&ptr, val1);
						if (dump_flag) {
							printf("'%s':", val1);
							break;
						}
						if (*cp == 'D')
							break;
						s = pnpval_as_str(cp + 2, pnpinfo);
						if (strcmp(s, val1) != 0)
							notme++;
						break;
						/* Key override fields, required to be last in the string */
					case 'T':
						/*
						 * This is imperfect and only does one key and will be redone
						 * to be more general for multiple keys. Currently, nothing
						 * does that.
						 */
						if (dump_flag)				/* No per-row data stored */
							break;
						if (cp[strlen(cp) - 1] == ';')		/* Skip required ; at end */
							cp[strlen(cp) - 1] = '\0';	/* in case it's not there */
						if ((s = strstr(pnpinfo, cp + 2)) == NULL)
							notme++;
						else if (s > pnpinfo && s[-1] != ' ')
							notme++;
						break;
					default:
						fprintf(stderr, "Unknown field type %c\n:", *cp);
						break;
					}
					bit++;
					cp = strchr(cp, ';');
					if (cp)
						cp++;
				} while (cp && *cp);
				if (dump_flag)
					printf("\n");
				else if (!notme) {
					if (!unbound_flag) {
						if (all_flag)
							printf("%s: %s", *dev ? dev : "unattached", lastmod);
						else
							printf("%s\n", lastmod);
						if (verbose_flag)
							printf("Matches --- %s ---\n", lastmod);
					}
					found++;
				}
			}
			break;
		default:
			if (dump_flag)
				printf("Unknown Type %d len %d\n", ival, len);
			break;
		}
		walker = (void *)(len - sizeof(int) + (intptr_t)walker);
	}
	if (unbound_flag && found == 0 && *pnpinfo) {
		if (verbose_flag)
			printf("------------------------- ");
		printf("%s on %s pnpinfo %s", *dev ? dev : "unattached", bus, pnpinfo);
		if (verbose_flag)
			printf(" -------------------------");
		printf("\n");
	}
	free(lastmod);
}
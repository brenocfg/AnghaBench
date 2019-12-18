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
struct moduledir {int d_hintsz; int /*<<< orphan*/ * d_hints; } ;

/* Variables and functions */
#define  MDT_MODULE 130 
#define  MDT_PNP_INFO 129 
#define  MDT_VERSION 128 
 int /*<<< orphan*/  free (char*) ; 
 int getint (void**) ; 
 int /*<<< orphan*/  getstr (void**,char*) ; 
 int /*<<< orphan*/  moduledir_readhints (struct moduledir*) ; 
 int /*<<< orphan*/  pnp_dump_flag ; 
 scalar_t__ pnp_unbound_flag ; 
 scalar_t__ pnp_verbose_flag ; 
 int pnpval_as_int (char*,char const*) ; 
 char* pnpval_as_str (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static char *
devmatch_search_hints(struct moduledir *mdp, const char *bus, const char *dev, const char *pnpinfo)
{
	char val1[256], val2[256];
	int ival, len, ents, i, notme, mask, bit, v, found;
	void *ptr, *walker, *hints_end;
	char *lastmod = NULL, *cp, *s;

	moduledir_readhints(mdp);
	found = 0;
	if (mdp->d_hints == NULL)
		goto bad;
	walker = mdp->d_hints;
	hints_end = walker + mdp->d_hintsz;
	while (walker < hints_end && !found) {
		len = getint(&walker);
		ival = getint(&walker);
		ptr = walker;
		switch (ival) {
		case MDT_VERSION:
			getstr(&ptr, val1);
			ival = getint(&ptr);
			getstr(&ptr, val2);
			if (pnp_dump_flag || pnp_verbose_flag)
				printf("Version: if %s.%d kmod %s\n", val1, ival, val2);
			break;
		case MDT_MODULE:
			getstr(&ptr, val1);
			getstr(&ptr, val2);
			if (lastmod)
				free(lastmod);
			lastmod = strdup(val2);
			if (pnp_dump_flag || pnp_verbose_flag)
				printf("module %s in %s\n", val1, val1);
			break;
		case MDT_PNP_INFO:
			if (!pnp_dump_flag && !pnp_unbound_flag && lastmod && strcmp(lastmod, "kernel") == 0)
				break;
			getstr(&ptr, val1);
			getstr(&ptr, val2);
			ents = getint(&ptr);
			if (pnp_dump_flag || pnp_verbose_flag)
				printf("PNP info for bus %s format %s %d entries (%s)\n",
				    val1, val2, ents, lastmod);
			if (strcmp(val1, "usb") == 0) {
				if (pnp_verbose_flag)
					printf("Treating usb as uhub -- bug in source table still?\n");
				strcpy(val1, "uhub");
			}
			if (bus && strcmp(val1, bus) != 0) {
				if (pnp_verbose_flag)
					printf("Skipped because table for bus %s, looking for %s\n",
					    val1, bus);
				break;
			}
			for (i = 0; i < ents; i++) {
				if (pnp_verbose_flag)
					printf("---------- Entry %d ----------\n", i);
				if (pnp_dump_flag)
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
						if (pnp_dump_flag) {
							printf("%#x:", ival);
							break;
						}
						if (bit >= 0 && ((1 << bit) & mask) == 0)
							break;
						v = pnpval_as_int(cp + 2, pnpinfo);
						if (pnp_verbose_flag)
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
						if (pnp_dump_flag) {
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
						if (pnp_dump_flag)				/* No per-row data stored */
							break;
						if (cp[strlen(cp) - 1] == ';')		/* Skip required ; at end */
							cp[strlen(cp) - 1] = '\0';	/* in case it's not there */
						if ((s = strstr(pnpinfo, cp + 2)) == NULL)
							notme++;
						else if (s > pnpinfo && s[-1] != ' ')
							notme++;
						break;
					default:
						printf("Unknown field type %c\n:", *cp);
						break;
					}
					bit++;
					cp = strchr(cp, ';');
					if (cp)
						cp++;
				} while (cp && *cp);
				if (pnp_dump_flag)
					printf("\n");
				else if (!notme) {
					if (!pnp_unbound_flag) {
						if (pnp_verbose_flag)
							printf("Matches --- %s ---\n", lastmod);
					}
					found++;
				}
			}
			break;
		default:
			break;
		}
		walker = (void *)(len - sizeof(int) + (intptr_t)walker);
	}
	if (pnp_unbound_flag && found == 0 && *pnpinfo) {
		if (pnp_verbose_flag)
			printf("------------------------- ");
		printf("%s on %s pnpinfo %s", *dev ? dev : "unattached", bus, pnpinfo);
		if (pnp_verbose_flag)
			printf(" -------------------------");
		printf("\n");
	}
	if (found != 0)
		return (lastmod);
	free(lastmod);

bad:
	return (NULL);
}
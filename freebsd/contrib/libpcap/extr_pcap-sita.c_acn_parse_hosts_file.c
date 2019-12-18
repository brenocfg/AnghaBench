#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ip; int chassis; int geoslot; } ;
typedef  TYPE_1__ unit_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_CHASSIS ; 
 int MAX_GEOSLOT ; 
 int MAX_LINE_SIZE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  empty_unit_table () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strcspn (char*,char*) ; 
 int strlen (char*) ; 
 int strspn (char*,char*) ; 
 char* strstr (char*,char*) ; 
 TYPE_1__** units ; 

int acn_parse_hosts_file(char *errbuf) {				/* returns: -1 = error, 0 = OK */
	FILE	*fp;
	char	buf[MAX_LINE_SIZE];
	char	*ptr, *ptr2;
	int		pos;
	int		chassis, geoslot;
	unit_t	*u;

	empty_unit_table();
	if ((fp = fopen("/etc/hosts", "r")) == NULL) {										/* try to open the hosts file and if it fails */
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "Cannot open '/etc/hosts' for reading.");	/* return the nohostsfile error response */
		return -1;
	}
	while (fgets(buf, MAX_LINE_SIZE-1, fp)) {			/* while looping over the file */

		pos = strcspn(buf, "#\n\r");					/* find the first comment character or EOL */
		*(buf + pos) = '\0';							/* and clobber it and anything that follows it */

		pos = strspn(buf, " \t");						/* then find the first non-white space */
		if (pos == strlen(buf))							/* if there is nothing but white space on the line */
			continue;									/* ignore that empty line */
		ptr = buf + pos;								/* and skip over any of that leading whitespace */

		if ((ptr2 = strstr(ptr, "_I_")) == NULL)		/* skip any lines that don't have names that look like they belong to IOPs */
			continue;
		if (*(ptr2 + 4) != '_')							/* and skip other lines that have names that don't look like ACN components */
			continue;
		*(ptr + strcspn(ptr, " \t")) = '\0';			/* null terminate the IP address so its a standalone string */

		chassis = *(ptr2 + 3) - '0';					/* extract the chassis number */
		geoslot = *(ptr2 + 5) - '0';					/* and geo-slot number */
		if (chassis < 1 || chassis > MAX_CHASSIS ||
			geoslot < 1 || geoslot > MAX_GEOSLOT) {		/* if the chassis and/or slot numbers appear to be bad... */
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "Invalid ACN name in '/etc/hosts'.");	/* warn the user */
			continue;																	/* and ignore the entry */
		}
		if ((ptr2 = (char *)malloc(strlen(ptr) + 1)) == NULL) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			continue;
		}
		strcpy(ptr2, ptr);								/* copy the IP address into our malloc'ed memory */
		u = &units[chassis][geoslot];
		u->ip = ptr2;									/* and remember the whole shebang */
		u->chassis = chassis;
		u->geoslot = geoslot;
	}
	fclose(fp);
	if (*errbuf)	return -1;
	else			return 0;
}
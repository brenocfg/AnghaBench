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
struct pcap_etherent {int* addr; char* name; } ;
typedef  int /*<<< orphan*/  e ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (int) ; 
 scalar_t__ isxdigit (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int skip_line (int /*<<< orphan*/ *) ; 
 int skip_space (int /*<<< orphan*/ *) ; 
 int xdtoi (int) ; 

struct pcap_etherent *
pcap_next_etherent(FILE *fp)
{
	register int c, i;
	u_char d;
	char *bp;
	size_t namesize;
	static struct pcap_etherent e;

	memset((char *)&e, 0, sizeof(e));
	for (;;) {
		/* Find addr */
		c = skip_space(fp);
		if (c == EOF)
			return (NULL);
		if (c == '\n')
			continue;

		/* If this is a comment, or first thing on line
		   cannot be Ethernet address, skip the line. */
		if (!isxdigit(c)) {
			c = skip_line(fp);
			if (c == EOF)
				return (NULL);
			continue;
		}

		/* must be the start of an address */
		for (i = 0; i < 6; i += 1) {
			d = xdtoi((u_char)c);
			c = getc(fp);
			if (c == EOF)
				return (NULL);
			if (isxdigit(c)) {
				d <<= 4;
				d |= xdtoi((u_char)c);
				c = getc(fp);
				if (c == EOF)
					return (NULL);
			}
			e.addr[i] = d;
			if (c != ':')
				break;
			c = getc(fp);
			if (c == EOF)
				return (NULL);
		}

		/* Must be whitespace */
		if (!isspace(c)) {
			c = skip_line(fp);
			if (c == EOF)
				return (NULL);
			continue;
		}
		c = skip_space(fp);
		if (c == EOF)
			return (NULL);

		/* hit end of line... */
		if (c == '\n')
			continue;

		if (c == '#') {
			c = skip_line(fp);
			if (c == EOF)
				return (NULL);
			continue;
		}

		/* pick up name */
		bp = e.name;
		/* Use 'namesize' to prevent buffer overflow. */
		namesize = sizeof(e.name) - 1;
		do {
			*bp++ = (u_char)c;
			c = getc(fp);
			if (c == EOF)
				return (NULL);
		} while (!isspace(c) && --namesize != 0);
		*bp = '\0';

		/* Eat trailing junk */
		if (c != '\n')
			(void)skip_line(fp);

		return &e;
	}
}
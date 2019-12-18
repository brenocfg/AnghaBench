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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int LDNS_MAX_PACKETLEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t hexstr2bin (char*,int,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isascii (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (scalar_t__*) ; 
 scalar_t__* xmalloc (int) ; 

__attribute__((used)) static size_t
packetbuffromfile(char *filename, uint8_t *wire)
{
	FILE *fp = NULL;
	int c;
	
	/* stat hack
	 * 0 = normal
	 * 1 = comment (skip to end of line)
	 * 2 = unprintable character found, read binary data directly
	 */
	int state = 0;
	uint8_t *hexbuf = xmalloc(LDNS_MAX_PACKETLEN);
	int hexbufpos = 0;
	size_t wirelen;
	
	if (strncmp(filename, "-", 2) == 0) {
		fp = stdin;
	} else {
		fp = fopen(filename, "r");
	}
	if (fp == NULL) {
		perror("Unable to open file for reading");
		xfree(hexbuf);
		return 0;
	}

	/*verbose("Opened %s\n", filename);*/
	
	c = fgetc(fp);
	while (c != EOF && hexbufpos < LDNS_MAX_PACKETLEN) {
		if (state < 2 && !isascii(c)) {
			/*verbose("non ascii character found in file: (%d) switching to raw mode\n", c);*/
			state = 2;
		}
		switch (state) {
			case 0:
				if (	(c >= '0' && c <= '9') ||
					(c >= 'a' && c <= 'f') ||
					(c >= 'A' && c <= 'F') )
				{
					hexbuf[hexbufpos] = (uint8_t) c;
					hexbufpos++;
				} else if (c == ';') {
					state = 1;
				} else if (c == ' ' || c == '\t' || c == '\n') {
					/* skip whitespace */
				} 
				break;
			case 1:
				if (c == '\n' || c == EOF) {
					state = 0;
				}
				break;
			case 2:
				hexbuf[hexbufpos] = (uint8_t) c;
				hexbufpos++;
				break;
		}
		c = fgetc(fp);
	}

	if (c == EOF) {
		/*
		if (have_drill_opt && drill_opt->verbose) {
			verbose("END OF FILE REACHED\n");
			if (state < 2) {
				verbose("read:\n");
				verbose("%s\n", hexbuf);
			} else {
				verbose("Not printing wire because it contains non ascii data\n");
			}
		}
		*/
	}
	if (hexbufpos >= LDNS_MAX_PACKETLEN) {
		/*verbose("packet size reached\n");*/
	}
	
	/* lenient mode: length must be multiple of 2 */
	if (hexbufpos % 2 != 0) {
		hexbuf[hexbufpos] = (uint8_t) '0';
		hexbufpos++;
	}

	if (state < 2) {
		wirelen = hexstr2bin((char *) hexbuf,
						 hexbufpos,
						 wire,
						 0,
						 LDNS_MAX_PACKETLEN);
	} else {
		memcpy(wire, hexbuf, (size_t) hexbufpos);
		wirelen = (size_t) hexbufpos;
	}
	if (fp != stdin) {
		fclose(fp);
	}
	xfree(hexbuf);
	return wirelen;
}
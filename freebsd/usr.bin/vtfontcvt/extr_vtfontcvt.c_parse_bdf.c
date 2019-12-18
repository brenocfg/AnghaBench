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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int add_char (unsigned int,unsigned int,char*,char*) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int height ; 
 unsigned int howmany (int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rshift_row (char*,int,int) ; 
 int /*<<< orphan*/  set_height (int) ; 
 int /*<<< orphan*/  set_width (int) ; 
 int split_row (char*,char*,char*,int) ; 
 scalar_t__ sscanf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 unsigned int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int wbytes ; 
 scalar_t__ width ; 
 char* xmalloc (int) ; 

__attribute__((used)) static int
parse_bdf(FILE *fp, unsigned int map_idx)
{
	char *line, *ln, *p;
	size_t length;
	uint8_t *bytes, *bytes_r;
	unsigned int curchar = 0, i, j, linenum = 0, bbwbytes;
	int bbw, bbh, bbox, bboy;		/* Glyph bounding box. */
	int fbbw = 0, fbbh, fbbox, fbboy;	/* Font bounding box. */
	int dwidth = 0, dwy = 0;
	int rv = -1;
	char spc = '\0';

	/*
	 * Step 1: Parse FONT logical font descriptor and FONTBOUNDINGBOX
	 * bounding box.
	 */
	while ((ln = fgetln(fp, &length)) != NULL) {
		linenum++;
		ln[length - 1] = '\0';

		if (strncmp(ln, "FONT ", 5) == 0) {
			p = ln + 5;
			i = 0;
			while ((p = strchr(p, '-')) != NULL) {
				p++;
				i++;
				if (i == 11) {
					spc = *p;
					break;
				}
			}
		} else if (strncmp(ln, "FONTBOUNDINGBOX ", 16) == 0) {
			if (sscanf(ln + 16, "%d %d %d %d", &fbbw, &fbbh, &fbbox,
			    &fbboy) != 4)
				errx(1, "invalid FONTBOUNDINGBOX at line %u",
				    linenum);
			set_width(fbbw);
			set_height(fbbh);
			break;
		}
	}
	if (fbbw == 0)
		errx(1, "broken font header");
	if (spc != 'c' && spc != 'C')
		errx(1, "font spacing \"C\" (character cell) required");

	/* Step 2: Validate DWIDTH (Device Width) of all glyphs. */
	while ((ln = fgetln(fp, &length)) != NULL) {
		linenum++;
		ln[length - 1] = '\0';

		if (strncmp(ln, "DWIDTH ", 7) == 0) {
			if (sscanf(ln + 7, "%d %d", &dwidth, &dwy) != 2)
				errx(1, "invalid DWIDTH at line %u", linenum);
			if (dwy != 0 || (dwidth != fbbw && dwidth * 2 != fbbw))
				errx(1, "bitmap with unsupported DWIDTH %d %d at line %u",
				    dwidth, dwy, linenum);
			if (dwidth < fbbw)
				set_width(dwidth);
		}
	}

	/* Step 3: Restart at the beginning of the file and read glyph data. */
	dwidth = bbw = bbh = 0;
	rewind(fp);
	linenum = 0;
	bbwbytes = 0; /* GCC 4.2.1 "may be used uninitialized" workaround. */
	bytes = xmalloc(wbytes * height);
	bytes_r = xmalloc(wbytes * height);
	line = xmalloc(wbytes * 2);
	while ((ln = fgetln(fp, &length)) != NULL) {
		linenum++;
		ln[length - 1] = '\0';

		if (strncmp(ln, "ENCODING ", 9) == 0) {
			curchar = atoi(ln + 9);
		} else if (strncmp(ln, "DWIDTH ", 7) == 0) {
			dwidth = atoi(ln + 7);
		} else if (strncmp(ln, "BBX ", 4) == 0) {
			if (sscanf(ln + 4, "%d %d %d %d", &bbw, &bbh, &bbox,
			     &bboy) != 4)
				errx(1, "invalid BBX at line %u", linenum);
			if (bbw < 1 || bbh < 1 || bbw > fbbw || bbh > fbbh ||
			    bbox < fbbox || bboy < fbboy ||
			    bbh + bboy > fbbh + fbboy)
				errx(1, "broken bitmap with BBX %d %d %d %d at line %u",
				    bbw, bbh, bbox, bboy, linenum);
			bbwbytes = howmany(bbw, 8);
		} else if (strncmp(ln, "BITMAP", 6) == 0 &&
		    (ln[6] == ' ' || ln[6] == '\0')) {
			if (dwidth == 0 || bbw == 0 || bbh == 0)
				errx(1, "broken char header at line %u!",
				    linenum);
			memset(bytes, 0, wbytes * height);
			memset(bytes_r, 0, wbytes * height);

			/*
			 * Assume that the next _bbh_ lines are bitmap data.
			 * ENDCHAR is allowed to terminate the bitmap
			 * early but is not otherwise checked; any extra data
			 * is ignored.
			 */
			for (i = (fbbh + fbboy) - (bbh + bboy);
			    i < (unsigned int)((fbbh + fbboy) - bboy); i++) {
				if ((ln = fgetln(fp, &length)) == NULL)
					errx(1, "unexpected EOF");
				linenum++;
				ln[length - 1] = '\0';
				if (strcmp(ln, "ENDCHAR") == 0)
					break;
				if (strlen(ln) < bbwbytes * 2)
					errx(1, "broken bitmap at line %u",
					    linenum);
				memset(line, 0, wbytes * 2);
				for (j = 0; j < bbwbytes; j++) {
					unsigned int val;
					if (sscanf(ln + j * 2, "%2x", &val) ==
					    0)
						break;
					*(line + j) = (uint8_t)val;
				}

				rshift_row(line, wbytes * 2, bbox - fbbox);
				rv = split_row(bytes + i * wbytes,
				     bytes_r + i * wbytes, line, dwidth);
				if (rv != 0)
					goto out;
			}

			rv = add_char(curchar, map_idx, bytes,
			    dwidth > (int)width ? bytes_r : NULL);
			if (rv != 0)
				goto out;

			dwidth = bbw = bbh = 0;
		}
	}

out:
	free(bytes);
	free(bytes_r);
	free(line);
	return (rv);
}
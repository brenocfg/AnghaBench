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
 int add_char (unsigned int,unsigned int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int height ; 
 unsigned int howmany (unsigned int,int) ; 
 int /*<<< orphan*/  set_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_width (int /*<<< orphan*/ ) ; 
 int split_row (scalar_t__*,scalar_t__*,scalar_t__*,unsigned int) ; 
 scalar_t__ sscanf (char*,char*,unsigned int*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int wbytes ; 
 int width ; 
 scalar_t__* xmalloc (int) ; 

__attribute__((used)) static int
parse_hex(FILE *fp, unsigned int map_idx)
{
	char *ln, *p;
	size_t length;
	uint8_t *bytes = NULL, *bytes_r = NULL, *line = NULL;
	unsigned curchar = 0, gwidth, gwbytes, i, j, chars_per_row;
	int rv = 0;

	while ((ln = fgetln(fp, &length)) != NULL) {
		ln[length - 1] = '\0';

		if (strncmp(ln, "# Height: ", 10) == 0) {
			if (bytes != NULL)
				errx(1, "malformed input: Height tag after font data");
			set_height(atoi(ln + 10));
		} else if (strncmp(ln, "# Width: ", 9) == 0) {
			if (bytes != NULL)
				errx(1, "malformed input: Width tag after font data");
			set_width(atoi(ln + 9));
		} else if (sscanf(ln, "%6x:", &curchar)) {
			if (bytes == NULL) {
				bytes = xmalloc(wbytes * height);
				bytes_r = xmalloc(wbytes * height);
				line = xmalloc(wbytes * 2);
			}
			/* ln is guaranteed to have a colon here. */
			p = strchr(ln, ':') + 1;
			chars_per_row = strlen(p) / height;
			if (chars_per_row < wbytes * 2)
				errx(1,
				    "malformed input: broken bitmap, character %06x",
				    curchar);
			gwidth = width * 2;
			gwbytes = howmany(gwidth, 8);
			if (chars_per_row < gwbytes * 2 || gwidth <= 8) {
				gwidth = width; /* Single-width character. */
				gwbytes = wbytes;
			}

			for (i = 0; i < height; i++) {
				for (j = 0; j < gwbytes; j++) {
					unsigned int val;
					if (sscanf(p + j * 2, "%2x", &val) == 0)
						break;
					*(line + j) = (uint8_t)val;
				}
				rv = split_row(bytes + i * wbytes,
				    bytes_r + i * wbytes, line, gwidth);
				if (rv != 0)
					goto out;
				p += gwbytes * 2;
			}

			rv = add_char(curchar, map_idx, bytes,
			    gwidth != width ? bytes_r : NULL);
			if (rv != 0)
				goto out;
		}
	}
out:
	free(bytes);
	free(bytes_r);
	free(line);
	return (rv);
}
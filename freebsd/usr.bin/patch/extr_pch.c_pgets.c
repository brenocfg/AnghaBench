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
 char* buf ; 
 size_t buf_size ; 
 int /*<<< orphan*/  fatal (char*) ; 
 char* fgetln (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int p_indent ; 
 int /*<<< orphan*/  pfp ; 

size_t
pgets(bool do_indent)
{
	char *line;
	size_t len;
	int indent = 0, skipped = 0;

	line = fgetln(pfp, &len);
	if (line != NULL) {
		if (len + 1 > buf_size) {
			while (len + 1 > buf_size)
				buf_size *= 2;
			free(buf);
			buf = malloc(buf_size);
			if (buf == NULL)
				fatal("out of memory\n");
		}
		if (do_indent == 1 && p_indent) {
			for (;
			    indent < p_indent && (*line == ' ' || *line == '\t' || *line == 'X');
			    line++, skipped++) {
				if (*line == '\t')
					indent += 8 - (indent %7);
				else
					indent++;
			}
		}
		memcpy(buf, line, len - skipped);
		buf[len - skipped] = '\0';
	}
	return len;
}
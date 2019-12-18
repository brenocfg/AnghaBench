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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXPORTS_LINE_SIZE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exports_clear () ; 
 unsigned int exports_file ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (unsigned int,char*) ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  g_gate_xlog (char*,...) ; 
 int /*<<< orphan*/  line_parse (char*,unsigned int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static void
exports_get(void)
{
	char buf[EXPORTS_LINE_SIZE], *line;
	unsigned lineno = 0, objs = 0, len;
	FILE *fd;

	exports_clear();

	fd = fopen(exports_file, "r");
	if (fd == NULL) {
		g_gate_xlog("Cannot open exports file (%s): %s.", exports_file,
		    strerror(errno));
	}

	g_gate_log(LOG_INFO, "Reading exports file (%s).", exports_file);

	for (;;) {
		if (fgets(buf, sizeof(buf), fd) == NULL) {
			if (feof(fd))
				break;

			g_gate_xlog("Error while reading exports file: %s.",
			    strerror(errno));
		}

		/* Increase line count. */
		lineno++;

		/* Skip spaces and tabs. */
		for (line = buf; *line == ' ' || *line == '\t'; ++line)
			;

		/* Empty line, comment or empty line at the end of file. */
		if (*line == '\n' || *line == '#' || *line == '\0')
			continue;

		len = strlen(line);
		if (line[len - 1] == '\n') {
			/* Remove new line char. */
			line[len - 1] = '\0';
		} else {
			if (!feof(fd))
				g_gate_xlog("Line %u too long.", lineno);
		}

		line_parse(line, lineno);
		objs++;
	}

	fclose(fd);

	if (objs == 0)
		g_gate_xlog("There are no objects to export.");

	g_gate_log(LOG_INFO, "Exporting %u object(s).", objs);
}
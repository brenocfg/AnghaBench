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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (int) ; 
 scalar_t__ parse (char*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
parsefile(const char *filename)
{
	FILE *file;
	char line[BUFSIZ], *p, *pq, *pdq;
	int warncount = 0, lineno = 0;

	file = fopen(filename, "r");
	if (file == NULL)
		err(EX_NOINPUT, "%s", filename);
	while (fgets(line, sizeof(line), file) != NULL) {
		lineno++;
		p = line;
		pq = strchr(line, '\'');
		pdq = strchr(line, '\"');
		/* Replace the first # with \0. */
		while((p = strchr(p, '#')) != NULL) {
			if (pq != NULL && p > pq) {
				if ((p = strchr(pq+1, '\'')) != NULL)
					*(++p) = '\0';
				break;
			} else if (pdq != NULL && p > pdq) {
				if ((p = strchr(pdq+1, '\"')) != NULL)
					*(++p) = '\0';
				break;
			} else if (p == line || *(p-1) != '\\') {
				*p = '\0';
				break;
			}
			p++;
		}
		/* Trim spaces */
		p = line + strlen(line) - 1;
		while (p >= line && isspace((int)*p)) {
			*p = '\0';
			p--;
		}
		p = line;
		while (isspace((int)*p))
			p++;
		if (*p == '\0')
			continue;
		else
			warncount += parse(p, lineno);
	}
	fclose(file);

	return (warncount);
}
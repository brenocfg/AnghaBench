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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  filenode ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BEFORE_LEN ; 
 int /*<<< orphan*/  BEFORE_STR ; 
 int KEYWORDS_LEN ; 
 int /*<<< orphan*/  KEYWORDS_STR ; 
 int KEYWORD_LEN ; 
 int /*<<< orphan*/  KEYWORD_STR ; 
 int PROVIDES_LEN ; 
 int /*<<< orphan*/  PROVIDES_STR ; 
 int PROVIDE_LEN ; 
 int /*<<< orphan*/  PROVIDE_STR ; 
 int REQUIRES_LEN ; 
 int /*<<< orphan*/  REQUIRES_STR ; 
 int REQUIRE_LEN ; 
 int /*<<< orphan*/  REQUIRE_STR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filenode_new (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* fparseln (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  parse_before (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_keywords (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_provide (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_require (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void
crunch_file(char *filename)
{
	FILE *fp;
	char *buf;
	int require_flag, provide_flag, before_flag, keywords_flag;
	enum { BEFORE_PARSING, PARSING, PARSING_DONE } state;
	filenode *node;
	char delims[3] = { '\\', '\\', '\0' };
	struct stat st;

	if ((fp = fopen(filename, "r")) == NULL) {
		warn("could not open %s", filename);
		return;
	}

	if (fstat(fileno(fp), &st) == -1) {
		warn("could not stat %s", filename);
		fclose(fp);
		return;
	}

	if (!S_ISREG(st.st_mode)) {
#if 0
		warnx("%s is not a file", filename);
#endif
		fclose(fp);
		return;
	}

	node = filenode_new(filename);

	/*
	 * we don't care about length, line number, don't want # for comments,
	 * and have no flags.
	 */
	for (state = BEFORE_PARSING; state != PARSING_DONE &&
	    (buf = fparseln(fp, NULL, NULL, delims, 0)) != NULL; free(buf)) {
		require_flag = provide_flag = before_flag = keywords_flag = 0;
		if (strncmp(REQUIRE_STR, buf, REQUIRE_LEN) == 0)
			require_flag = REQUIRE_LEN;
		else if (strncmp(REQUIRES_STR, buf, REQUIRES_LEN) == 0)
			require_flag = REQUIRES_LEN;
		else if (strncmp(PROVIDE_STR, buf, PROVIDE_LEN) == 0)
			provide_flag = PROVIDE_LEN;
		else if (strncmp(PROVIDES_STR, buf, PROVIDES_LEN) == 0)
			provide_flag = PROVIDES_LEN;
		else if (strncmp(BEFORE_STR, buf, BEFORE_LEN) == 0)
			before_flag = BEFORE_LEN;
		else if (strncmp(KEYWORD_STR, buf, KEYWORD_LEN) == 0)
			keywords_flag = KEYWORD_LEN;
		else if (strncmp(KEYWORDS_STR, buf, KEYWORDS_LEN) == 0)
			keywords_flag = KEYWORDS_LEN;
		else {
			if (state == PARSING)
				state = PARSING_DONE;
			continue;
		}

		state = PARSING;
		if (require_flag)
			parse_require(node, buf + require_flag);
		else if (provide_flag)
			parse_provide(node, buf + provide_flag);
		else if (before_flag)
			parse_before(node, buf + before_flag);
		else if (keywords_flag)
			parse_keywords(node, buf + keywords_flag);
	}
	fclose(fp);
}
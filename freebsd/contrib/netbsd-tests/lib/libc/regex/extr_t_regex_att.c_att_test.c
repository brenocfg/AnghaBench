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
struct atf_tc {int dummy; } ;
typedef  char regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  data_path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int,...) ; 
 int MAXPATHLEN ; 
 int REG_BASIC ; 
 int REG_EXTENDED ; 
 int REG_NOSPEC ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char*) ; 
 char* atf_tc_get_config_var (struct atf_tc const*,char*) ; 
 scalar_t__ bug (char*,char*,size_t) ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  checkcomment (char*,size_t) ; 
 int /*<<< orphan*/  checkmatches (char*,size_t,char*,size_t) ; 
 int /*<<< orphan*/  delim ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* fparseln (int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  geterror (char*,int*,int*) ; 
 int getflags (char*) ; 
 size_t getmatches (char*) ; 
 int /*<<< orphan*/  optional (char*) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int regexec (int /*<<< orphan*/ *,char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sep ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 int strunvis (char*,char*) ; 
 int /*<<< orphan*/  unsupported (char*) ; 

__attribute__((used)) static void
att_test(const struct atf_tc *tc, const char *data_name)
{
	regex_t re;
	char *line, *lastpattern = NULL, data_path[MAXPATHLEN];
	size_t len, lineno = 0;
	int skipping = 0;
	FILE *input_file;

	snprintf(data_path, sizeof(data_path), "%s/data/%s.dat",
	    atf_tc_get_config_var(tc, "srcdir"), data_name);

	input_file = fopen(data_path, "r");
	if (input_file == NULL)
		atf_tc_fail("Failed to open input file %s", data_path);

	for (; (line = fparseln(input_file, &len, &lineno, delim, 0))
	    != NULL; free(line)) {
		char *name, *pattern, *input, *matches, *comment;
		regmatch_t *pm;
		size_t nm;
#ifdef DEBUG
		fprintf(stderr, "[%s]\n", line);
#endif
		if ((name = strtok(line, sep)) == NULL)
			continue;

		/*
		 * We check these early so that we skip the lines quickly
		 * in order to do more strict testing on the other arguments
		 * The same characters are also tested in the switch below
		 */
		if (*name == '}') {
			skipping = 0;
			continue;
		}
		if (skipping)
			continue;
		if (*name == ';' || *name == '#' || strcmp(name, "NOTE") == 0)
			continue;
		if (*name == ':') {
			/* Skip ":HA#???:" prefix */
			while (*++name && *name != ':')
				continue;
			if (*name)
				name++;
		}

		ATF_REQUIRE_MSG((pattern = strtok(NULL, sep)) != NULL,
			"Missing pattern at line %zu", lineno);
		ATF_REQUIRE_MSG((input = strtok(NULL, sep)) != NULL,
			"Missing input at line %zu", lineno);

		if (strchr(name, '$')) {
			ATF_REQUIRE(strunvis(pattern, pattern) != -1);
			ATF_REQUIRE(strunvis(input, input) != -1);
		}


		if (strcmp(input, "NULL") == 0)
			*input = '\0';

		if (strcmp(pattern, "SAME") == 0) {
			ATF_REQUIRE(lastpattern != NULL);
			pattern = lastpattern;
		} else {
			free(lastpattern);
			ATF_REQUIRE((lastpattern = strdup(pattern)) != NULL);
		}

		ATF_REQUIRE_MSG((matches = strtok(NULL, sep)) != NULL,
		    "Missing matches at line %zu", lineno);

		comment = strtok(NULL, sep);
		switch (*name) {
		case '{':	/* Begin optional implementation */
			if (optional(comment)) {
				skipping++;
				continue;
			}
			name++;	/* We have it, so ignore */
			break;
		case '}':	/* End optional implementation */
			skipping = 0;
			continue;
		case '?':	/* Optional */
		case '|':	/* Alternative */
			if (unsupported(comment))
				continue;
			name++;	/* We have it, so ignore */
			break;
		case '#':	/* Comment */
		case ';':	/* Skip */
			continue;
		default:
			break;
		}

		/* XXX: Our bug */
		if (bug(pattern, input, lineno))
			continue;

		int comp, exec;
		if (*matches != '(') {
			geterror(matches, &comp, &exec);
			pm = NULL;
			nm = 0;
		} else {
			comp = exec = 0;
			nm = getmatches(matches);
			ATF_REQUIRE((pm = calloc(nm, sizeof(*pm))) != NULL);
		}



		int iflags = getflags(name);
		for (; *name; name++) {
			int flags;
			switch (*name) {
			case 'B':
				flags = REG_BASIC;
				break;
			case 'E':
				flags = REG_EXTENDED;
				break;
			case 'L':
				flags = REG_NOSPEC;
				break;
			default:
				ATF_REQUIRE_MSG(0, "Bad name %c", *name);
				continue;
			}
			int c = regcomp(&re, pattern, flags | iflags);
			ATF_REQUIRE_MSG(c == comp,
			    "regcomp returned %d for pattern %s at line %zu",
			    c, pattern, lineno);
			if (c)
				continue;
			int e = regexec(&re, input, nm, pm, 0);
			ATF_REQUIRE_MSG(e == exec, "Expected error %d,"
			    " got %d at line %zu", exec, e, lineno);
			checkmatches(matches, nm, pm, lineno);
			checkcomment(comment, lineno);
			regfree(&re);
		}
		free(pm);
	}

	fclose(input_file);
}
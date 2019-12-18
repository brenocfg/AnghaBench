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
struct tm {int tm_mon; int tm_mday; int tm_year; scalar_t__ tm_wday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  dbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  D_MD_ORDER ; 
 int F_VARIABLE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int MAXCOUNT ; 
 int /*<<< orphan*/  REPLACE (char*,int,int /*<<< orphan*/ ) ; 
#define  T_ERR 130 
#define  T_OK 129 
#define  T_PROCESS 128 
 scalar_t__ debug ; 
 int /*<<< orphan*/  doall ; 
 int /*<<< orphan*/  event_add (int,int,int,char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_continue (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * events ; 
 int /*<<< orphan*/ * extradata ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncny ; 
 int /*<<< orphan*/  ndecsolstice ; 
 int /*<<< orphan*/  neaster ; 
 int /*<<< orphan*/  nfullmoon ; 
 int /*<<< orphan*/  njunsolstice ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmarequinox ; 
 int /*<<< orphan*/  nnewmoon ; 
 int /*<<< orphan*/  npaskha ; 
 int /*<<< orphan*/  nsepequinox ; 
 int parsedaymonth (char*,int*,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_new_encoding () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setnnames () ; 
 int /*<<< orphan*/  setnsequences (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int token (char*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
cal_parse(FILE *in, FILE *out)
{
	char *line = NULL;
	char *buf;
	size_t linecap = 0;
	ssize_t linelen;
	ssize_t l;
	static int d_first = -1;
	static int count = 0;
	int i;
	int month[MAXCOUNT];
	int day[MAXCOUNT];
	int year[MAXCOUNT];
	bool skip = false;
	char dbuf[80];
	char *pp, p;
	struct tm tm;
	int flags;

	/* Unused */
	tm.tm_sec = 0;
	tm.tm_min = 0;
	tm.tm_hour = 0;
	tm.tm_wday = 0;

	if (in == NULL)
		return (1);

	while ((linelen = getline(&line, &linecap, in)) > 0) {
		if (*line == '#') {
			switch (token(line+1, out, &skip)) {
			case T_ERR:
				free(line);
				return (1);
			case T_OK:
				continue;
			case T_PROCESS:
				break;
			default:
				break;
			}
		}

		if (skip)
			continue;

		buf = line;
		for (l = linelen;
		     l > 0 && isspace((unsigned char)buf[l - 1]);
		     l--)
			;
		buf[l] = '\0';
		if (buf[0] == '\0')
			continue;

		/*
		 * Setting LANG in user's calendar was an old workaround
		 * for 'calendar -a' being run with C locale to properly
		 * print user's calendars in their native languages.
		 * Now that 'calendar -a' does fork with setusercontext(),
		 * and does not run iconv(), this variable has little use.
		 */
		if (strncmp(buf, "LANG=", 5) == 0) {
			(void)setlocale(LC_ALL, buf + 5);
			d_first = (*nl_langinfo(D_MD_ORDER) == 'd');
#ifdef WITH_ICONV
			if (!doall)
				set_new_encoding();
#endif
			setnnames();
			continue;
		}
		/* Parse special definitions: Easter, Paskha etc */
		REPLACE("Easter=", 7, neaster);
		REPLACE("Paskha=", 7, npaskha);
		REPLACE("ChineseNewYear=", 15, ncny);
		REPLACE("NewMoon=", 8, nnewmoon);
		REPLACE("FullMoon=", 9, nfullmoon);
		REPLACE("MarEquinox=", 11, nmarequinox);
		REPLACE("SepEquinox=", 11, nsepequinox);
		REPLACE("JunSolstice=", 12, njunsolstice);
		REPLACE("DecSolstice=", 12, ndecsolstice);
		if (strncmp(buf, "SEQUENCE=", 9) == 0) {
			setnsequences(buf + 9);
			continue;
		}

		/*
		 * If the line starts with a tab, the data has to be
		 * added to the previous line
		 */
		if (buf[0] == '\t') {
			for (i = 0; i < count; i++)
				event_continue(events[i], buf);
			continue;
		}

		/* Get rid of leading spaces (non-standard) */
		while (isspace((unsigned char)buf[0]))
			memcpy(buf, buf + 1, strlen(buf));

		/* No tab in the line, then not a valid line */
		if ((pp = strchr(buf, '\t')) == NULL)
			continue;

		/* Trim spaces in front of the tab */
		while (isspace((unsigned char)pp[-1]))
			pp--;

		p = *pp;
		*pp = '\0';
		if ((count = parsedaymonth(buf, year, month, day, &flags,
		    extradata)) == 0)
			continue;
		*pp = p;
		if (count < 0) {
			/* Show error status based on return value */
			if (debug)
				fprintf(stderr, "Ignored: %s\n", buf);
			if (count == -1)
				continue;
			count = -count + 1;
		}

		/* Find the last tab */
		while (pp[1] == '\t')
			pp++;

		if (d_first < 0)
			d_first = (*nl_langinfo(D_MD_ORDER) == 'd');

		for (i = 0; i < count; i++) {
			tm.tm_mon = month[i] - 1;
			tm.tm_mday = day[i];
			tm.tm_year = year[i] - 1900;
			(void)strftime(dbuf, sizeof(dbuf),
			    d_first ? "%e %b" : "%b %e", &tm);
			if (debug)
				fprintf(stderr, "got %s\n", pp);
			events[i] = event_add(year[i], month[i], day[i], dbuf,
			    ((flags &= F_VARIABLE) != 0) ? 1 : 0, pp,
			    extradata[i]);
		}
	}

	free(line);
	fclose(in);

	return (0);
}
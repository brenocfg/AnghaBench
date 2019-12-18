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
struct jobspec_hdr {int dummy; } ;
struct jobspec {int startnum; int endrange; char* wantedhost; char* wanteduser; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct jobspec_hdr*,struct jobspec*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct jobspec*) ; 
 scalar_t__ isdigitch (char) ; 
 struct jobspec* malloc (int) ; 
 int /*<<< orphan*/  memset (struct jobspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nextjs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strchr (char*,char) ; 
 int strtol (char*,char**,int) ; 

int
parse_jobspec(char *jobstr, struct jobspec_hdr *js_hdr)
{
	struct jobspec *jsinfo;
	char *atsign, *colon, *lhside, *numstr, *period, *rhside;
	int jobnum;

#if DEBUG_PARSEJS
	printf("\t [ pjs-input = %s ]\n", jobstr);
#endif

	if ((jobstr == NULL) || (*jobstr == '\0'))
		return (0);

	jsinfo = malloc(sizeof(struct jobspec));
	memset(jsinfo, 0, sizeof(struct jobspec));
	jsinfo->startnum = jsinfo->endrange = -1;

	/* Find the separator characters, and nullify them. */
	numstr = NULL;
	atsign = strchr(jobstr, '@');
	colon = strchr(jobstr, ':');
	if (atsign != NULL)
		*atsign = '\0';
	if (colon != NULL)
		*colon = '\0';

	/* The at-sign always indicates a hostname. */
	if (atsign != NULL) {
		rhside = atsign + 1;
		if (*rhside != '\0')
			jsinfo->wantedhost = rhside;
	}

	/* Finish splitting the input into three parts. */
	rhside = NULL;
	if (colon != NULL) {
		rhside = colon + 1;
		if (*rhside == '\0')
			rhside = NULL;
	}
	lhside = NULL;
	if (*jobstr != '\0')
		lhside = jobstr;

	/*
	 * If there is a `:' here, then it's either jobrange:userid,
	 * userid:jobrange, or (if @hostname was not given) perhaps it
	 * might be hostname:jobnum.  The side which has a digit as the
	 * first character is assumed to be the jobrange.  It is an
	 * input error if both sides start with a digit, or if neither
	 * side starts with a digit.
	 */
	if ((lhside != NULL) && (rhside != NULL)) {
		if (isdigitch(*lhside)) {
			if (isdigitch(*rhside))
				goto bad_input;
			numstr = lhside;
			jsinfo->wanteduser = rhside;
		} else if (isdigitch(*rhside)) {
			numstr = rhside;
			/*
			 * The original implementation of 'lpc topq' accepted
			 * hostname:jobnum.  If the input did not include a
			 * @hostname, then assume the userid is a hostname if
			 * it includes a '.'.
			 */
			period = strchr(lhside, '.');
			if ((atsign == NULL) && (period != NULL))
				jsinfo->wantedhost = lhside;
			else
				jsinfo->wanteduser = lhside;
		} else {
			/* Neither side is a job number = user error */
			goto bad_input;
		}
	} else if (lhside != NULL) {
		if (isdigitch(*lhside))
			numstr = lhside;
		else
			jsinfo->wanteduser = lhside;
	} else if (rhside != NULL) {
		if (isdigitch(*rhside))
			numstr = rhside;
		else
			jsinfo->wanteduser = rhside;
	}

	/*
	 * Break down the numstr.  It should be all digits, or a range
	 * specified as "\d+-\d+".
	 */
	if (numstr != NULL) {
		errno = 0;
		jobnum = strtol(numstr, &numstr, 10);
		if (errno != 0)		/* error in conversion */
			goto bad_input;
		if (jobnum < 0)		/* a bogus value for this purpose */
			goto bad_input;
		if (jobnum > 99999)	/* too large for job number */
			goto bad_input;
		jsinfo->startnum = jsinfo->endrange = jobnum;

		/* Check for a range of numbers */
		if ((*numstr == '-') && (isdigitch(*(numstr + 1)))) {
			numstr++;
			errno = 0;
			jobnum = strtol(numstr, &numstr, 10);
			if (errno != 0)		/* error in conversion */
				goto bad_input;
			if (jobnum < jsinfo->startnum)
				goto bad_input;
			if (jobnum > 99999)	/* too large for job number */
				goto bad_input;
			jsinfo->endrange = jobnum;
		}

		/*
		 * If there is anything left in the numstr, and if the
		 * original string did not include a userid or a hostname,
		 * then this might be the ancient form of '\d+hostname'
		 * (with no separator between jobnum and hostname).  Accept
		 * that for backwards compatibility, but otherwise any
		 * remaining characters mean a user-error.  Note that the
		 * ancient form accepted only a single number, but this
		 * will also accept a range of numbers.
		 */
		if (*numstr != '\0') {
			if (atsign != NULL)
				goto bad_input;
			if (jsinfo->wantedhost != NULL)
				goto bad_input;
			if (jsinfo->wanteduser != NULL)
				goto bad_input;
			/* Treat as the rest of the string as a hostname */
			jsinfo->wantedhost = numstr;
		}
	}

	if ((jsinfo->startnum < 0) && (jsinfo->wanteduser == NULL) &&
	    (jsinfo->wantedhost == NULL))
		goto bad_input;

	/*
	 * The input was valid, in the sense that it could be parsed
	 * into the individual parts.  Add this jobspec to the list
	 * of jobspecs.
	 */
	STAILQ_INSERT_TAIL(js_hdr, jsinfo, nextjs);

#if DEBUG_PARSEJS
	printf("\t [   will check for");
	if (jsinfo->startnum >= 0) {
		if (jsinfo->startnum == jsinfo->endrange)
			printf(" jobnum = %ld", jsinfo->startnum);
		else
			printf(" jobrange = %ld to %ld", jsinfo->startnum,
			    jsinfo->endrange);
	} else {
		printf(" jobs");
	}
	if ((jsinfo->wanteduser != NULL) || (jsinfo->wantedhost != NULL)) {
		printf(" from");
		if (jsinfo->wanteduser != NULL)
			printf(" user = %s", jsinfo->wanteduser);
		if (jsinfo->wantedhost != NULL)
			printf(" host = %s", jsinfo->wantedhost);
	}
	printf("]\n");
#endif

	return (1);

bad_input:
	/*
	 * Restore any `@' and `:', in case the calling routine wants to
	 * write an error message which includes the input string.
	 */
	if (atsign != NULL)
		*atsign = '@';
	if (colon != NULL)
		*colon = ':';
	if (jsinfo != NULL)
		free(jsinfo);
	return (0);
}
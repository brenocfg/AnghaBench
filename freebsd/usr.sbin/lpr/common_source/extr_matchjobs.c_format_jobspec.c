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
struct jobspec {char* fmtoutput; int pluralfmt; char* wanteduser; char* wantedhost; int /*<<< orphan*/  startnum; int /*<<< orphan*/  endrange; } ;
typedef  int /*<<< orphan*/  rangestr ;
typedef  int /*<<< orphan*/  buildstr ;

/* Variables and functions */
#define  FMTJS_TERSE 129 
#define  FMTJS_VERBOSE 128 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

void
format_jobspec(struct jobspec *jspec, int fmt_wanted)
{
	char rangestr[40], buildstr[200];
	const char fromuser[] = "from user ";
	const char fromhost[] = "from host ";
	size_t strsize;

	/*
	 * If the struct already has a fmtstring, then release it
	 * before building a new one.
	 */
	if (jspec->fmtoutput != NULL) {
		free(jspec->fmtoutput);
		jspec->fmtoutput = NULL;
	}

	jspec->pluralfmt = 1;		/* assume a "plural result" */
	rangestr[0] = '\0';
	if (jspec->startnum >= 0) {
		if (jspec->startnum != jspec->endrange)
			snprintf(rangestr, sizeof(rangestr), "%ld-%ld",
			    jspec->startnum, jspec->endrange);
		else {
			jspec->pluralfmt = 0;
			snprintf(rangestr, sizeof(rangestr), "%ld",
			    jspec->startnum);
		}
	}

	strsize = sizeof(buildstr);
	buildstr[0] = '\0';
	switch (fmt_wanted) {
	case FMTJS_TERSE:
		/* Build everything but the hostname in a temp string. */
		if (jspec->wanteduser != NULL)
			strlcat(buildstr, jspec->wanteduser, strsize);
		if (rangestr[0] != '\0') {
			if (buildstr[0] != '\0')
				strlcat(buildstr, ":", strsize);
			strlcat(buildstr, rangestr, strsize);
		}
		if (jspec->wantedhost != NULL)
				strlcat(buildstr, "@", strsize);

		/* Get space for the final result, including hostname */
		strsize = strlen(buildstr) + 1;
		if (jspec->wantedhost != NULL)
			strsize += strlen(jspec->wantedhost);
		jspec->fmtoutput = malloc(strsize);

		/* Put together the final result */
		strlcpy(jspec->fmtoutput, buildstr, strsize);
		if (jspec->wantedhost != NULL)
			strlcat(jspec->fmtoutput, jspec->wantedhost, strsize);
		break;

	case FMTJS_VERBOSE:
	default:
		/* Build everything but the hostname in a temp string. */
		strlcat(buildstr, rangestr, strsize);
		if (jspec->wanteduser != NULL) {
			if (rangestr[0] != '\0')
				strlcat(buildstr, " ", strsize);
			strlcat(buildstr, fromuser, strsize);
			strlcat(buildstr, jspec->wanteduser, strsize);
		}
		if (jspec->wantedhost != NULL) {
			if (jspec->wanteduser == NULL) {
				if (rangestr[0] != '\0')
					strlcat(buildstr, " ", strsize);
				strlcat(buildstr, fromhost, strsize);
			} else
				strlcat(buildstr, "@", strsize);
		}

		/* Get space for the final result, including hostname */
		strsize = strlen(buildstr) + 1;
		if (jspec->wantedhost != NULL)
			strsize += strlen(jspec->wantedhost);
		jspec->fmtoutput = malloc(strsize);

		/* Put together the final result */
		strlcpy(jspec->fmtoutput, buildstr, strsize);
		if (jspec->wantedhost != NULL)
			strlcat(jspec->fmtoutput, jspec->wantedhost, strsize);
		break;
	}
}
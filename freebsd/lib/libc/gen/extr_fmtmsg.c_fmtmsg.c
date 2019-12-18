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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DFLT_MSGVERB ; 
 long MM_CONSOLE ; 
 int MM_NOCON ; 
 int MM_NOTOK ; 
 int MM_OK ; 
 long MM_PRINT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* printfmt (char*,long,char const*,int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * stderr ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ validmsgverb (char*) ; 

int
fmtmsg(long class, const char *label, int sev, const char *text,
    const char *action, const char *tag)
{
	FILE *fp;
	char *env, *msgverb, *output;

	if (class & MM_PRINT) {
		if ((env = getenv("MSGVERB")) != NULL && *env != '\0' &&
		    strlen(env) <= strlen(DFLT_MSGVERB)) {
			if ((msgverb = strdup(env)) == NULL)
				return (MM_NOTOK);
			else if (validmsgverb(msgverb) == 0) {
				free(msgverb);
				goto def;
			}
		} else {
def:
			if ((msgverb = strdup(DFLT_MSGVERB)) == NULL)
				return (MM_NOTOK);
		}
		output = printfmt(msgverb, class, label, sev, text, action,
		    tag);
		if (output == NULL) {
			free(msgverb);
			return (MM_NOTOK);
		}
		if (*output != '\0')
			fprintf(stderr, "%s", output);
		free(msgverb);
		free(output);
	}
	if (class & MM_CONSOLE) {
		output = printfmt(DFLT_MSGVERB, class, label, sev, text,
		    action, tag);
		if (output == NULL)
			return (MM_NOCON);
		if (*output != '\0') {
			if ((fp = fopen("/dev/console", "ae")) == NULL) {
				free(output);
				return (MM_NOCON);
			}
			fprintf(fp, "%s", output);
			fclose(fp);
		}
		free(output);
	}
	return (MM_OK);
}
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
struct message {int dummy; } ;
typedef  int /*<<< orphan*/  namebuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINESIZE ; 
 char* hfield (char*,struct message*) ; 
 scalar_t__ readline (int /*<<< orphan*/ *,char*,int) ; 
 char* savestr (char*) ; 
 int /*<<< orphan*/ * setinput (struct message*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

char *
name1(struct message *mp, int reptype)
{
	char namebuf[LINESIZE];
	char linebuf[LINESIZE];
	char *cp, *cp2;
	FILE *ibuf;
	int first = 1;

	if ((cp = hfield("from", mp)) != NULL)
		return (cp);
	if (reptype == 0 && (cp = hfield("sender", mp)) != NULL)
		return (cp);
	ibuf = setinput(mp);
	namebuf[0] = '\0';
	if (readline(ibuf, linebuf, LINESIZE) < 0)
		return (savestr(namebuf));
newname:
	for (cp = linebuf; *cp != '\0' && *cp != ' '; cp++)
		;
	for (; *cp == ' ' || *cp == '\t'; cp++)
		;
	for (cp2 = &namebuf[strlen(namebuf)];
	    *cp != '\0' && *cp != ' ' && *cp != '\t' &&
	    cp2 < namebuf + LINESIZE - 1;)
		*cp2++ = *cp++;
	*cp2 = '\0';
	if (readline(ibuf, linebuf, LINESIZE) < 0)
		return (savestr(namebuf));
	if ((cp = strchr(linebuf, 'F')) == NULL)
		return (savestr(namebuf));
	if (strncmp(cp, "From", 4) != 0)
		return (savestr(namebuf));
	while ((cp = strchr(cp, 'r')) != NULL) {
		if (strncmp(cp, "remote", 6) == 0) {
			if ((cp = strchr(cp, 'f')) == NULL)
				break;
			if (strncmp(cp, "from", 4) != 0)
				break;
			if ((cp = strchr(cp, ' ')) == NULL)
				break;
			cp++;
			if (first) {
				cp2 = namebuf;
				first = 0;
			} else
				cp2 = strrchr(namebuf, '!') + 1;
			strlcpy(cp2, cp, sizeof(namebuf) - (cp2 - namebuf) - 1);
			strcat(namebuf, "!");
			goto newname;
		}
		cp++;
	}
	return (savestr(namebuf));
}
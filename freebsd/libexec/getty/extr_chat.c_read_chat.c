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
 int /*<<< orphan*/  PAUSE_CH ; 
 int /*<<< orphan*/  free (char*) ; 
 void* getdigit (unsigned char**,int,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/ * strcpy (char*,char*) ; 
 int strlen (char*) ; 
 unsigned char* strrchr (char*,char) ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char **
read_chat(char **chatstr)
{
	char *str = *chatstr;
	char **res = NULL;

	if (str != NULL) {
		char *tmp = NULL;
		int l;

		if ((l=strlen(str)) > 0 && (tmp=malloc(l + 1)) != NULL &&
		    (res=malloc(((l + 1) / 2 + 1) * sizeof(char *))) != NULL) {
			static char ws[] = " \t";
			char * p;

			for (l = 0, p = strtok(strcpy(tmp, str), ws);
			     p != NULL;
			     p = strtok(NULL, ws))
			{
				unsigned char *q, *r;

				/* Read escapes */
				for (q = r = (unsigned char *)p; *r; ++q)
				{
					if (*q == '\\')
					{
						/* handle special escapes */
						switch (*++q)
						{
						case 'a': /* bell */
							*r++ = '\a';
							break;
						case 'r': /* cr */
							*r++ = '\r';
							break;
						case 'n': /* nl */
							*r++ = '\n';
							break;
						case 'f': /* ff */
							*r++ = '\f';
							break;
						case 'b': /* bs */
							*r++ = '\b';
							break;
						case 'e': /* esc */
							*r++ = 27;
							break;
						case 't': /* tab */
							*r++ = '\t';
							break;
						case 'p': /* pause */
							*r++ = PAUSE_CH;
							break;
						case 's':
						case 'S': /* space */
							*r++ = ' ';
							break;
						case 'x': /* hexdigit */
							++q;
							*r++ = getdigit(&q, 16, 2);
							--q;
							break;
						case '0': /* octal */
							++q;
							*r++ = getdigit(&q, 8, 3);
							--q;
							break;
						default: /* literal */
							*r++ = *q;
							break;
						case 0: /* not past eos */
							--q;
							break;
						}
					} else {
						/* copy standard character */
						*r++ = *q;
					}
				}

				/* Remove surrounding quotes, if any
				 */
				if (*p == '"' || *p == '\'') {
					q = strrchr(p+1, *p);
					if (q != NULL && *q == *p && q[1] == '\0') {
						*q = '\0';
						p++;
					}
				}

				res[l++] = p;
			}
			res[l] = NULL;
			*chatstr = tmp;
			return res;
		}
		free(tmp);
	}
	return res;
}
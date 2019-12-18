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
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

char *
get_quoted_word(FILE *fp)
{
	static char line[256];
	int ch;
	char *cp;
	int escaped_nl = 0;

begin:
	while ((ch = getc(fp)) != EOF)
		if (ch != ' ' && ch != '\t')
			break;
	if (ch == EOF)
		return ((char *)EOF);
	if (ch == '\\'){
		escaped_nl = 1;
		goto begin;
	}
	if (ch == '\n') {
		if (escaped_nl){
			escaped_nl = 0;
			goto begin;
		}
		else
			return (NULL);
	}
	cp = line;
	if (ch == '"' || ch == '\'') {
		int quote = ch;

		escaped_nl = 0;
		while ((ch = getc(fp)) != EOF) {
			if (ch == quote && !escaped_nl)
				break;
			if (ch == '\n' && !escaped_nl) {
				*cp = 0;
				printf("config: missing quote reading `%s'\n",
					line);
				exit(2);
			}
			if (ch == '\\' && !escaped_nl) {
				escaped_nl = 1;
				continue;
			}
			if (ch != quote && escaped_nl)
				*cp++ = '\\';
			*cp++ = ch;
			escaped_nl = 0;
		}
	} else {
		*cp++ = ch;
		while ((ch = getc(fp)) != EOF) {
			if (isspace(ch))
				break;
			*cp++ = ch;
		}
		if (ch != EOF)
			(void) ungetc(ch, fp);
	}
	*cp = 0;
	if (ch == EOF)
		return ((char *)EOF);
	return (line);
}
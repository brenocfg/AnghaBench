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
struct lex {char l_char; int l_token; } ;

/* Variables and functions */
 int STRINGLEN ; 
 int TEOL ; 
 int TERROR ; 
 int TNUMBER ; 
 int TSTRING ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int lexnumber ; 
 char* lexstring ; 
 int* numberstack ; 
 size_t regretp ; 
 int* regretstack ; 
 struct lex* singles ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * string_stack ; 

int
scan(char **sp)
{
	char *cp, *cp2;
	int c;
	struct lex *lp;
	int quotec;

	if (regretp >= 0) {
		strcpy(lexstring, string_stack[regretp]);
		lexnumber = numberstack[regretp];
		return (regretstack[regretp--]);
	}
	cp = *sp;
	cp2 = lexstring;
	c = *cp++;

	/*
	 * strip away leading white space.
	 */

	while (c == ' ' || c == '\t')
		c = *cp++;

	/*
	 * If no characters remain, we are at end of line,
	 * so report that.
	 */

	if (c == '\0') {
		*sp = --cp;
		return (TEOL);
	}

	/*
	 * If the leading character is a digit, scan
	 * the number and convert it on the fly.
	 * Return TNUMBER when done.
	 */

	if (isdigit((unsigned char)c)) {
		lexnumber = 0;
		while (isdigit((unsigned char)c)) {
			lexnumber = lexnumber*10 + c - '0';
			*cp2++ = c;
			c = *cp++;
		}
		*cp2 = '\0';
		*sp = --cp;
		return (TNUMBER);
	}

	/*
	 * Check for single character tokens; return such
	 * if found.
	 */

	for (lp = &singles[0]; lp->l_char != '\0'; lp++)
		if (c == lp->l_char) {
			lexstring[0] = c;
			lexstring[1] = '\0';
			*sp = cp;
			return (lp->l_token);
		}

	/*
	 * We've got a string!  Copy all the characters
	 * of the string into lexstring, until we see
	 * a null, space, or tab.
	 * If the lead character is a " or ', save it
	 * and scan until you get another.
	 */

	quotec = 0;
	if (c == '\'' || c == '"') {
		quotec = c;
		c = *cp++;
	}
	while (c != '\0') {
		if (c == quotec) {
			cp++;
			break;
		}
		if (quotec == 0 && (c == ' ' || c == '\t'))
			break;
		if (cp2 - lexstring < STRINGLEN-1)
			*cp2++ = c;
		c = *cp++;
	}
	if (quotec && c == '\0') {
		fprintf(stderr, "Missing %c\n", quotec);
		return (TERROR);
	}
	*sp = --cp;
	*cp2 = '\0';
	return (TSTRING);
}
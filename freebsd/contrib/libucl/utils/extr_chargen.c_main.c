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
 scalar_t__ isalnum (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ isprint (int) ; 
 scalar_t__ isspace (int) ; 
 scalar_t__ print_flag (char*,int*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

int
main (int argc, char **argv)
{
	int i, col, r;
	const char *name = "ucl_chartable";
	bool need_or;
	char valbuf[2048];

	col = 0;

	if (argc > 1) {
		name = argv[1];
	}

	printf ("static const unsigned int %s[256] = {\n", name);

	for (i = 0; i < 256; i ++) {
		need_or = false;
		r = 0;
		/* UCL_CHARACTER_VALUE_END */

		if (i == ' ' || i == '\t') {
			r += print_flag ("UCL_CHARACTER_WHITESPACE", &need_or, valbuf + r);
		}
		if (isspace (i)) {
			r += print_flag ("UCL_CHARACTER_WHITESPACE_UNSAFE", &need_or, valbuf + r);
		}
		if (isalnum (i) || i >= 0x80 || i == '/' || i == '_') {
			r += print_flag ("UCL_CHARACTER_KEY_START", &need_or, valbuf + r);
		}
		if (isalnum (i) || i == '-' || i == '_' || i == '/' || i == '.' || i >= 0x80) {
			r += print_flag ("UCL_CHARACTER_KEY", &need_or, valbuf + r);
		}
		if (i == 0 || i == '\r' || i == '\n' || i == ']' || i == '}' || i == ';' || i == ',' || i == '#') {
			r += print_flag ("UCL_CHARACTER_VALUE_END", &need_or, valbuf + r);
		}
		else {
			if (isprint (i) || i >= 0x80) {
				r += print_flag ("UCL_CHARACTER_VALUE_STR", &need_or, valbuf + r);
			}
			if (isdigit (i) || i == '-') {
				r += print_flag ("UCL_CHARACTER_VALUE_DIGIT_START", &need_or, valbuf + r);
			}
			if (isalnum (i) || i == '.' || i == '-' || i == '+') {
				r += print_flag ("UCL_CHARACTER_VALUE_DIGIT", &need_or, valbuf + r);
			}
		}
		if (i == '"' || i == '\\' || i == '/' || i == 'b' ||
			i == 'f' || i == 'n' || i == 'r' || i == 't' || i == 'u') {
			r += print_flag ("UCL_CHARACTER_ESCAPE", &need_or, valbuf + r);
		}
		if (i == ' ' || i == '\t' || i == ':' || i == '=') {
			r += print_flag ("UCL_CHARACTER_KEY_SEP", &need_or, valbuf + r);
		}
		if (i == '\n' || i == '\r' || i == '\\' || i == '\b' || i == '\t' ||
				i == '"' || i == '\f') {
			r += print_flag ("UCL_CHARACTER_JSON_UNSAFE", &need_or, valbuf + r);
		}
		if (i == '\n' || i == '\r' || i == '\\' || i == '\b' || i == '\t' ||
				i == '"' || i == '\f' || i == '=' || i == ':' || i == '{' || i == '[' || i == ' ') {
			r += print_flag ("UCL_CHARACTER_UCL_UNSAFE", &need_or, valbuf + r);
		}

		if (!need_or) {
			r += print_flag ("UCL_CHARACTER_DENIED", &need_or, valbuf + r);
		}

		if (isprint (i)) {
			r += sprintf (valbuf + r, " /* %c */", i);
		}
		if (i != 255) {
			r += sprintf (valbuf + r, ", ");
		}
		col += r;
		if (col > 80) {
			printf ("\n%s", valbuf);
			col = r;
		}
		else {
			printf ("%s", valbuf);
		}
	}
	printf ("\n}\n");

	return 0;
}
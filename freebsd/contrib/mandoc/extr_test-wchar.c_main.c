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
typedef  scalar_t__ wint_t ;
typedef  int wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 char* UTF8_LOCALE ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ putwchar (int) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int wcwidth (int) ; 

int
main(void)
{
	wchar_t	 wc;
	int	 width;

	if (setlocale(LC_ALL, "") == NULL) {
		fputs("setlocale(LC_ALL, \"\") failed\n", stderr);
		return 1;
	}

	if (setlocale(LC_CTYPE, UTF8_LOCALE) == NULL) {
		fprintf(stderr, "setlocale(LC_CTYPE, \"%s\") failed\n",
		    UTF8_LOCALE);
		return 1;
	}

	if (sizeof(wchar_t) < 4) {
		fprintf(stderr, "wchar_t is only %zu bytes\n",
		    sizeof(wchar_t));
		return 1;
	}

	if ((width = wcwidth(L' ')) != 1) {
		fprintf(stderr, "wcwidth(L' ') returned %d\n", width);
		return 1;
	}

	dup2(STDERR_FILENO, STDOUT_FILENO);
	wc = L'*';
	if (putwchar(wc) != (wint_t)wc) {
		fputs("bad putwchar return value\n", stderr);
		return 1;
	}

	return 0;
}
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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_line (int /*<<< orphan*/ *,size_t*) ; 
 size_t goal_length ; 
 scalar_t__ iswspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_errors ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintf (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
center_stream(FILE *stream, const char *name)
{
	wchar_t *line, *p;
	size_t length;
	size_t width;
	int cwidth;

	while ((line = get_line(stream, &length)) != NULL) {
		size_t l = length;

		while (l > 0 && iswspace(*line)) {
			++line;
			--l;
		}
		length = l;
		for (p = line, width = 0; p < &line[length]; p++)
			width += (cwidth = wcwidth(*p)) > 0 ? cwidth : 1;
		l = width;
		while (l < goal_length) {
			putwchar(' ');
			l += 2;
		}
		wprintf(L"%.*ls\n", (int)length, line);
	}
	if (ferror(stream)) {
		warn("%s", name);
		++n_errors;
	}
}
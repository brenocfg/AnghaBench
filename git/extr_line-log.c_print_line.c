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
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 char* get_nth_line (long,unsigned long*,void*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_line(const char *prefix, char first,
		       long line, unsigned long *ends, void *data,
		       const char *color, const char *reset, FILE *file)
{
	char *begin = get_nth_line(line, ends, data);
	char *end = get_nth_line(line+1, ends, data);
	int had_nl = 0;

	if (end > begin && end[-1] == '\n') {
		end--;
		had_nl = 1;
	}

	fputs(prefix, file);
	fputs(color, file);
	putc(first, file);
	fwrite(begin, 1, end-begin, file);
	fputs(reset, file);
	putc('\n', file);
	if (!had_nl)
		fputs("\\ No newline at end of file\n", file);
}
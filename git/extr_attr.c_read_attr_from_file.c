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
struct attr_stack {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 
 int /*<<< orphan*/  handle_attr_line (struct attr_stack*,char*,char const*,int,int) ; 
 int /*<<< orphan*/  skip_utf8_bom (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct attr_stack* xcalloc (int,int) ; 

__attribute__((used)) static struct attr_stack *read_attr_from_file(const char *path, int macro_ok)
{
	FILE *fp = fopen_or_warn(path, "r");
	struct attr_stack *res;
	char buf[2048];
	int lineno = 0;

	if (!fp)
		return NULL;
	res = xcalloc(1, sizeof(*res));
	while (fgets(buf, sizeof(buf), fp)) {
		char *bufp = buf;
		if (!lineno)
			skip_utf8_bom(&bufp, strlen(bufp));
		handle_attr_line(res, bufp, path, ++lineno, macro_ok);
	}
	fclose(fp);
	return res;
}
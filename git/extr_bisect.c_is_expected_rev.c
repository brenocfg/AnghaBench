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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 
 char* git_path_bisect_expected_rev () ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_expected_rev(const struct object_id *oid)
{
	const char *filename = git_path_bisect_expected_rev();
	struct stat st;
	struct strbuf str = STRBUF_INIT;
	FILE *fp;
	int res = 0;

	if (stat(filename, &st) || !S_ISREG(st.st_mode))
		return 0;

	fp = fopen_or_warn(filename, "r");
	if (!fp)
		return 0;

	if (strbuf_getline_lf(&str, fp) != EOF)
		res = !strcmp(str.buf, oid_to_hex(oid));

	strbuf_release(&str);
	fclose(fp);

	return res;
}
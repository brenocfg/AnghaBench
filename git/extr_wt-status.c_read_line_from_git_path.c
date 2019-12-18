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
struct strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path (char*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static char *read_line_from_git_path(const char *filename)
{
	struct strbuf buf = STRBUF_INIT;
	FILE *fp = fopen_or_warn(git_path("%s", filename), "r");

	if (!fp) {
		strbuf_release(&buf);
		return NULL;
	}
	strbuf_getline_lf(&buf, fp);
	if (!fclose(fp)) {
		return strbuf_detach(&buf, NULL);
	} else {
		strbuf_release(&buf);
		return NULL;
	}
}
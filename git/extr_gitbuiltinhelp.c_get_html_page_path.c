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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HTML_PATH ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* html_path ; 
 int /*<<< orphan*/  mkpath (char*,char*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 char* system_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_html_page_path(struct strbuf *page_path, const char *page)
{
	struct stat st;
	char *to_free = NULL;

	if (!html_path)
		html_path = to_free = system_path(GIT_HTML_PATH);

	/* Check that we have a git documentation directory. */
	if (!strstr(html_path, "://")) {
		if (stat(mkpath("%s/git.html", html_path), &st)
		    || !S_ISREG(st.st_mode))
			die("'%s': not a documentation directory.", html_path);
	}

	strbuf_init(page_path, 0);
	strbuf_addf(page_path, "%s/%s.html", html_path, page);
	free(to_free);
}
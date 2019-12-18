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
struct req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOCUS_QUERY ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  resp_begin_html (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_end_html () ; 
 int /*<<< orphan*/  resp_searchform (struct req const*,int /*<<< orphan*/ ) ; 
 char* scriptname ; 

__attribute__((used)) static void
pg_index(const struct req *req)
{

	resp_begin_html(200, NULL, NULL);
	resp_searchform(req, FOCUS_QUERY);
	printf("<p>\n"
	       "This web interface is documented in the\n"
	       "<a class=\"Xr\" href=\"/%s%sman.cgi.8\">man.cgi(8)</a>\n"
	       "manual, and the\n"
	       "<a class=\"Xr\" href=\"/%s%sapropos.1\">apropos(1)</a>\n"
	       "manual explains the query syntax.\n"
	       "</p>\n",
	       scriptname, *scriptname == '\0' ? "" : "/",
	       scriptname, *scriptname == '\0' ? "" : "/");
	resp_end_html();
}
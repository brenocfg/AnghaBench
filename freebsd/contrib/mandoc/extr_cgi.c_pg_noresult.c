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
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  resp_begin_html (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_end_html () ; 
 int /*<<< orphan*/  resp_searchform (struct req const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pg_noresult(const struct req *req, const char *msg)
{
	resp_begin_html(200, NULL, NULL);
	resp_searchform(req, FOCUS_QUERY);
	puts("<p>");
	puts(msg);
	puts("</p>");
	resp_end_html();
}
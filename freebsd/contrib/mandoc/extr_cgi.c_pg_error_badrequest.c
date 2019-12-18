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
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  resp_begin_html (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_end_html () ; 
 char* scriptname ; 

__attribute__((used)) static void
pg_error_badrequest(const char *msg)
{

	resp_begin_html(400, "Bad Request", NULL);
	puts("<h1>Bad Request</h1>\n"
	     "<p>\n");
	puts(msg);
	printf("Try again from the\n"
	       "<a href=\"/%s\">main page</a>.\n"
	       "</p>", scriptname);
	resp_end_html();
}
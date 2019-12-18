#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* manpath; int /*<<< orphan*/ * arch; int /*<<< orphan*/ * sec; int /*<<< orphan*/ * query; } ;
struct req {int psz; int /*<<< orphan*/ ** p; TYPE_1__ q; } ;
typedef  enum focus { ____Placeholder_focus } focus ;

/* Variables and functions */
 int FOCUS_QUERY ; 
 int arch_MAX ; 
 char** arch_names ; 
 int /*<<< orphan*/  html_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* scriptname ; 
 int sec_MAX ; 
 char** sec_names ; 
 char** sec_numbers ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
resp_searchform(const struct req *req, enum focus focus)
{
	int		 i;

	printf("<form action=\"/%s\" method=\"get\">\n"
	       "  <fieldset>\n"
	       "    <legend>Manual Page Search Parameters</legend>\n",
	       scriptname);

	/* Write query input box. */

	printf("    <input type=\"search\" name=\"query\" value=\"");
	if (req->q.query != NULL)
		html_print(req->q.query);
	printf( "\" size=\"40\"");
	if (focus == FOCUS_QUERY)
		printf(" autofocus");
	puts(">");

	/* Write submission buttons. */

	printf(	"    <button type=\"submit\" name=\"apropos\" value=\"0\">"
		"man</button>\n"
		"    <button type=\"submit\" name=\"apropos\" value=\"1\">"
		"apropos</button>\n"
		"    <br/>\n");

	/* Write section selector. */

	puts("    <select name=\"sec\">");
	for (i = 0; i < sec_MAX; i++) {
		printf("      <option value=\"%s\"", sec_numbers[i]);
		if (NULL != req->q.sec &&
		    0 == strcmp(sec_numbers[i], req->q.sec))
			printf(" selected=\"selected\"");
		printf(">%s</option>\n", sec_names[i]);
	}
	puts("    </select>");

	/* Write architecture selector. */

	printf(	"    <select name=\"arch\">\n"
		"      <option value=\"default\"");
	if (NULL == req->q.arch)
		printf(" selected=\"selected\"");
	puts(">All Architectures</option>");
	for (i = 0; i < arch_MAX; i++) {
		printf("      <option");
		if (NULL != req->q.arch &&
		    0 == strcmp(arch_names[i], req->q.arch))
			printf(" selected=\"selected\"");
		printf(">%s</option>\n", arch_names[i]);
	}
	puts("    </select>");

	/* Write manpath selector. */

	if (req->psz > 1) {
		puts("    <select name=\"manpath\">");
		for (i = 0; i < (int)req->psz; i++) {
			printf("      <option");
			if (strcmp(req->q.manpath, req->p[i]) == 0)
				printf(" selected=\"selected\"");
			printf(">");
			html_print(req->p[i]);
			puts("</option>");
		}
		puts("    </select>");
	}

	puts("  </fieldset>\n"
	     "</form>");
}
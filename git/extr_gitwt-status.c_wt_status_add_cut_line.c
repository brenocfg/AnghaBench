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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int comment_line_char ; 
 char* cut_line ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void wt_status_add_cut_line(FILE *fp)
{
	const char *explanation = _("Do not modify or remove the line above.\nEverything below it will be ignored.");
	struct strbuf buf = STRBUF_INIT;

	fprintf(fp, "%c %s", comment_line_char, cut_line);
	strbuf_add_commented_lines(&buf, explanation, strlen(explanation));
	fputs(buf.buf, fp);
	strbuf_release(&buf);
}